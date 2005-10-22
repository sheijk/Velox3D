<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet
  version="1.0"
  xmlns:exsl="http://exslt.org/common"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:func="http://exslt.org/functions"
  extension-element-prefixes="func"
>
  <xsl:output method="xml" encoding="iso-8859-1" indent="yes"/>
  
  <!-- 
   ! params 
   !-->
  <xsl:param name="__vcproj"/> <!-- project -->

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
   !  Template for workspace
   !-->
  <xsl:template match="projects">
    <projects>
      <!-- copy all existing projects -->
      <xsl:copy-of select="@*|node( )"/>
      <!-- insert new project -->
      <project name="{$__vcproj}" type="lib">
        <files/>
      </project>
    </projects>
  </xsl:template>
 
</xsl:stylesheet>
