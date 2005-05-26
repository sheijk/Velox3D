<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet
  version="1.0"
  xmlns:exsl="http://exslt.org/common"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:func="http://exslt.org/functions"
  extension-element-prefixes="func"
>
  <xsl:output method="text" encoding="iso-8859-1" indent="no"/>

  <!-- 
   ! params 
   !-->
  <xsl:param name="__project"/> <!-- .vcproj file -->

  <!--
   ! extract project type
   !-->
  <xsl:template match="//projects/project">
    <xsl:if test="@name = $__project">
      <xsl:value-of select="@type"/>
    </xsl:if>
  </xsl:template>
  
</xsl:stylesheet>
