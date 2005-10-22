<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet
  version="1.0"
  xmlns:exsl="http://exslt.org/common"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:func="http://exslt.org/functions"
  extension-element-prefixes="func"
>
  <xsl:include href="functions.xsl"/>

  <!-- 
   ! params 
   !-->
  <xsl:param name="__vcprojfile"/> <!-- .vcproj file -->
  <xsl:param name="__vcproj"/> <!-- project -->
  <!-- prefix to prepend the RelativePaths -->
  <xsl:param name="__prefix"/>

  <xsl:output method="xml" encoding="iso-8859-1" indent="yes" doctype-system="mbuild.dtd"/>

  <!-- read $__vcprojfile into a variable -->
  <xsl:variable name="vcprojfile">
    <xsl:call-template name="globalReplace">
      <xsl:with-param name="outputString" select="$__vcprojfile"/>
      <xsl:with-param name="target" select="' '"/>
      <xsl:with-param name="replacement" select="'%20'"/>
    </xsl:call-template>
  </xsl:variable>
  <xsl:variable name="__doc" select="document($vcprojfile)"/>

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
   ! template for projects
        <xsl:copy-of select="exsl:node-set($__doc)//File"/>
   !-->
  <xsl:template match="project">
    <!-- check if name matches -->
    <xsl:if test="$__vcproj = @name">
      <xsl:variable name="found">true</xsl:variable>
      <project>
        <xsl:attribute name="name"><xsl:value-of select="$__vcproj"/></xsl:attribute>
        <xsl:attribute name="type"><xsl:value-of select="@type"/></xsl:attribute>
        <!-- copy all subnodes but 'files' and 'file' -->
        <xsl:copy-of select=".//*[name() != 'files' and name() != 'file']"/>
        <!-- generate new files subnode from $__doc -->
        <files>
          <xsl:for-each select="exsl:node-set($__doc)//File">
            <!-- strip __prefix from @RelativePath -->
            <xsl:variable name="rpath">
              <xsl:call-template name="globalReplace">
                <xsl:with-param name="outputString" select="@RelativePath"/>
                <xsl:with-param name="target" select="$__prefix"/>
                <xsl:with-param name="replacement" select="''"/>
              </xsl:call-template>
            </xsl:variable>
            <!-- write new file node -->
            <file><xsl:value-of select="translate($rpath, '\', '/')"/></file>
          </xsl:for-each>
        </files>
      </project>
    </xsl:if>
    <!-- no else in xsl, just copy through -->
    <xsl:if test="$__vcproj != @name">
      <xsl:copy-of select="."/>
    </xsl:if>
  </xsl:template>

</xsl:stylesheet>
