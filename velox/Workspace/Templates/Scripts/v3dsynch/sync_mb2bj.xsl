<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet
  version="1.0"
  xmlns:exsl="http://exslt.org/common"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:func="http://exslt.org/functions"
  extension-element-prefixes="func"
>
  <xsl:output method="text" encoding="iso-8859-1" indent="no" media-type="text/plain"/>

  <!-- include functions -->
  <xsl:include href="func_bjam.xsl"/>

  <!-- 
   ! params 
   !-->
  <xsl:param name="project"/><!-- project -->


  <!-- template for projects -->
<xsl:template match="//project">
  <xsl:if test="@name = $project">
<xsl:apply-templates select="files"/> 
<xsl:apply-templates select="dependencies"/> 
  </xsl:if>
</xsl:template>

</xsl:stylesheet>
