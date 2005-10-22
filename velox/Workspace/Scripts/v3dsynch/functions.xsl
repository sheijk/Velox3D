<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet
  version="1.0"
  xmlns:exsl="http://exslt.org/common"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:func="http://exslt.org/functions"
  extension-element-prefixes="func"
>
  <!--
   ! strips dirnames recursively
   !
   ! @param  string file
   !-->
  <xsl:template name="stripdirs">
    <xsl:param name="file"/>
    <xsl:if test="not(contains($file, '/'))"><xsl:value-of select="$file"/></xsl:if>
    <xsl:variable name="nf"><xsl:value-of select="substring-after($file, '/')"/></xsl:variable>
    <xsl:if test="contains($nf, '/')">
      <xsl:call-template name="stripdirs">
        <xsl:with-param name="file"><xsl:value-of select="$nf"/></xsl:with-param>
      </xsl:call-template>
    </xsl:if>
    <xsl:if test="not(contains($nf, '/'))"><xsl:value-of select="$nf"/></xsl:if>
  </xsl:template>

  <!--
   ! basename function
   !
   ! @param  string file
   !-->
  <func:function name="func:basename">
    <xsl:param name="file"/>
    <!-- strip directories -->
    <xsl:variable name="wod"> 
      <xsl:call-template name="stripdirs">
        <xsl:with-param name="file"><xsl:value-of select="$file"/></xsl:with-param>
      </xsl:call-template>
    </xsl:variable>
    <func:result><xsl:value-of select="substring-before($wod, '.')"/></func:result>
  </func:function>

  
  <!-- 
   ! replaces text - ripped from http://www.xml.com/pub/a/2002/06/05/transforming.html
   !-->
  <xsl:template name="globalReplace">
    <xsl:param name="outputString"/>
    <xsl:param name="target"/>
    <xsl:param name="replacement"/>
    <xsl:choose>
      <xsl:when test="contains($outputString,$target)">
     
        <xsl:value-of select="concat(substring-before($outputString,$target), $replacement)"/>
        <xsl:call-template name="globalReplace">
          <xsl:with-param name="outputString" select="substring-after($outputString,$target)"/>
          <xsl:with-param name="target" select="$target"/>
          <xsl:with-param name="replacement" select="$replacement"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:otherwise>
        <xsl:value-of select="$outputString"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>  
 

</xsl:stylesheet>
