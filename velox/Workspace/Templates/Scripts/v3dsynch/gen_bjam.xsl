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
   !  Template for workspace
   !-->
  <xsl:template match="workspace">
################################################################################
# bjam file created by mbuild for workspace "<xsl:value-of select="@name"/>"
################################################################################

# settings common to all subprojects
#-------------------------------------------------------------------------------
project <xsl:value-of select="@name"/>
    :
    ;

    <!-- create projects -->
    <xsl:apply-templates select="projects"/>

    <!-- create obj targets -->
    <xsl:call-template name="objs"/>

  </xsl:template>




  <!--
   !  Template for projects
   !-->
  <xsl:template match="projects">
<xsl:for-each select="project">
# sub-project: <xsl:value-of select="@name"/>
#------------------------------------------------------------------------------
<!-- convert type -->
<xsl:value-of select="@type"/>
<xsl:text> </xsl:text><xsl:value-of select="@name"/><xsl:text>
    </xsl:text>
<!-- required files -->
    <xsl:apply-templates select="files"/>
<!-- other dependencies -->
  <xsl:apply-templates select="dependencies"/>
    ;
</xsl:for-each>
  </xsl:template>










</xsl:stylesheet>
