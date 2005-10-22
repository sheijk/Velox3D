<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet
  version="1.0"
  xmlns:exsl="http://exslt.org/common"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:func="http://exslt.org/functions"
  extension-element-prefixes="func"
>
  <xsl:output method="xml" encoding="iso-8859-1" indent="yes"/>
  <xsl:include href="functions.xsl"/>

  <!-- 
   ! params 
   !-->
  <xsl:param name="__mbfile"/> <!-- mbuild file -->
  <xsl:param name="__vcproj"/> <!-- project -->
  <!-- prefix to prepend the RelativePaths -->
  <xsl:param name="__prefix"/>

  <!-- read $__mbfile into a variable -->
  <xsl:variable name="mbfile">
    <xsl:call-template name="globalReplace">
      <xsl:with-param name="outputString" select="$__mbfile"/>
      <xsl:with-param name="target" select="' '"/>
      <xsl:with-param name="replacement" select="'%20'"/>
    </xsl:call-template>
  </xsl:variable>
  <xsl:variable name="__doc" select="document($mbfile)"/>

  <!--
   ! default copy template
   ! copies all nodes recursively
   !-->
  <xsl:template match="@*|node( )">
    <xsl:copy>
      <xsl:apply-templates select="@*|node( )"/>
    </xsl:copy>
  </xsl:template>


  <!--
   ! reorder path function
   ! ( Interface/ | Implementation/)([^/]+/)(.*) => $2$1$3
   ! @param  string file
   !-->
  <func:function name="func:reorderPath">
    <xsl:param name="file"/>
    <xsl:param name="key"/>

    <!-- remove $key/ -->
    <xsl:variable name="sanskey">
      <xsl:value-of select="substring-after($file, concat($key, '/'))"/>
    </xsl:variable>
    <xsl:variable name="result">
      <xsl:choose>
        <!-- check whether $key is in $file and $sanskey contains another slash -->
        <xsl:when test="contains($file, $key) and contains($sanskey, '/')">
          <!-- find part2 -->
          <xsl:variable name="part2">
            <xsl:value-of select="substring-before($sanskey, '/')"/>
          </xsl:variable>
          <!-- find part3 -->
          <xsl:variable name="part3">
            <xsl:value-of select="substring-after($sanskey, '/')"/>
          </xsl:variable>

          <!-- re-assemble parh -->
          <xsl:value-of select="concat($part2, '/', $key, '/', $part3)"/>
        </xsl:when>
        <!-- $key not in in $file, return $file -->
        <xsl:otherwise>
          <xsl:value-of select="$file"/>
        </xsl:otherwise>
      </xsl:choose>

    </xsl:variable> <!-- result -->

    <func:result><xsl:value-of select="$result"/></func:result>
  </func:function>

  <!--
   ! convert path function
   !
   ! @param  string file
   !-->
  <func:function name="func:convpath">
    <xsl:param name="file"/>
    <!-- remove prefix -->
    <xsl:variable name="noprefix">
      <xsl:call-template name="globalReplace">
        <xsl:with-param name="outputString" select="."/>
        <xsl:with-param name="target" select="$__prefix"/>
        <xsl:with-param name="replacement" select="''"/>
      </xsl:call-template>
    </xsl:variable>
    
    <!-- Source => Implementation -->
    <xsl:variable name="sourcerep">
      <xsl:call-template name="globalReplace">
        <xsl:with-param name="outputString" select="$noprefix"/>
        <xsl:with-param name="target" select="'Source'"/>
        <xsl:with-param name="replacement" select="'Implementation'"/>
      </xsl:call-template>
    </xsl:variable> 
    
    <!-- API/V3d => Interface -->
    <xsl:variable name="apirep">
      <xsl:call-template name="globalReplace">
        <xsl:with-param name="outputString" select="$sourcerep"/>
        <xsl:with-param name="target" select="'API/V3d'"/>
        <xsl:with-param name="replacement" select="'Interface'"/>
      </xsl:call-template>
    </xsl:variable> 

    <!-- return converted path  -->
    <func:result><xsl:value-of select="func:reorderPath(func:reorderPath($apirep, 'Interface'), 'Implementation')"/></func:result>
  </func:function>

  <!--
   ! template for projects
   !-->
  <xsl:template match="/VisualStudioProject/Files">
    <Files>    
    <xsl:apply-templates select="exsl:node-set($__doc)//project[@name = $__vcproj]/files"/>
    </Files>    
  </xsl:template>

  <!--
   ! matches the files node from the mbuild file
   !-->
  <xsl:template match="files">
    <xsl:variable name="folders">
      <!-- create a temporary tree with a folder structure -->
      <temp>
      <xsl:copy>
        <xsl:copy-of select="@*" />


        <xsl:for-each select="file">
          <!-- sort the files for nicer output -->
          <xsl:sort select="func:convpath(.)" />

          <!-- build a folder structure for each file (separately) -->
          <xsl:apply-templates select="." mode="build-folders">
            <xsl:with-param name="path" select="func:convpath(.)" />
          </xsl:apply-templates>
        </xsl:for-each>
      </xsl:copy>
      </temp>
    </xsl:variable>

    
    <!-- we have files in separate folder elements, now merge them --> 
    <xsl:apply-templates select="exsl:node-set($folders)/node()" mode="merge"/> 
    
    <!-- <DEBUG/>
    <xsl:copy-of select="$folders"/> -->
 
  </xsl:template>


  <!-- 
   ! builds a Filter/File tree for each file
   !-->
  <xsl:template match="file" mode="build-folders">
    <xsl:param name="path-base" />
    <xsl:param name="path" /> 

    <!-- folder-count equals the number of slashes in the path, minus one for the file name -->
    <xsl:param name="folder-count" select="string-length($path) - string-length(translate($path, '/', ''))  "/>

    <xsl:variable name="folder-name" select="substring-before($path, '/')" />
    <xsl:variable name="folder-path" select="concat($path-base, $folder-name, '/')" />
    <xsl:variable name="remainder" select="substring-after($path, '/')" />
    <xsl:choose>
      <!-- should not occur, actually -->
      <xsl:when test="string-length($path) = 0" />


      <!-- path contains slashes, output a folder -->
      <xsl:when test="$folder-count > 0">


        <folder name="{$folder-name}" path="{$folder-path}" remainder="{$remainder}">
          <xsl:apply-templates select="." mode="build-folders">
            <xsl:with-param name="path" select="$remainder" />
            <xsl:with-param name="path-base" select="$folder-path" />
          </xsl:apply-templates>
        </folder>
      </xsl:when>

      <!-- no more slashes, output the file -->
      <xsl:otherwise>
        <!-- note: why the fuck does $folder-patht have an additional / at the end? -->
        <entry fullpath="{.}" parent="{substring($folder-path, 1, string-length($folder-path)-1 )}"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:key name="me" match="folder" use="@path"/>
  <xsl:key name="parent" match="folder" use="parent::folder/@path"/>
  
  <!-- 
   ! matches folders and merges the trees 
   !-->
  <xsl:template match="folder" mode="merge">
    <xsl:variable name="mykey" select="@path"/> 
    <xsl:choose>
      <xsl:when test="generate-id(.) = generate-id(key('me',$mykey)[1])">
        <Filter Name="{@name}" Filter="">
          <xsl:apply-templates select="key('parent', $mykey)" mode="merge"/> 
          <xsl:apply-templates select="//entry" mode="merge">
            <xsl:with-param name="parent"><xsl:value-of select="@path"/></xsl:with-param>
          </xsl:apply-templates> 
        </Filter>
      </xsl:when>
    </xsl:choose>
  </xsl:template>

  <!-- 
   ! matches files for merge
   !-->
  <xsl:template match="entry" mode="merge">
    <xsl:param name="parent"/>
    <xsl:if test="@parent = $parent">
      <File RelativePath="{translate(@fullpath, '/', '\')}"/>
    </xsl:if>
  </xsl:template>


</xsl:stylesheet>
