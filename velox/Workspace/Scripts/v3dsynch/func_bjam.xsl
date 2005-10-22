<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet
  version="1.0"
  xmlns:exsl="http://exslt.org/common"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:func="http://exslt.org/functions"
  extension-element-prefixes="func"
>
  <xsl:output method="text" encoding="iso-8859-1" indent="no" media-type="text/plain"/>

  <!--  
   ! bjam
   ! common functionality
   !-->

  <!-- include functions -->
  <xsl:include href="functions.xsl"/>

  <!-- variable declaration -->
  <xsl:variable name="rootdir"><xsl:value-of select="workspace/@rootdir"/></xsl:variable>

  <!--
   !  Template for files
   !-->
  <xsl:template match="files">
<xsl:text>: # source files 
    </xsl:text>
    <xsl:for-each select="file">
      <!-- only export .cpp files -->
      <xsl:if test="contains(., '.cpp')">
          <xsl:value-of select="$rootdir"/><xsl:value-of select="."/><xsl:text>
    </xsl:text>
      </xsl:if>
    </xsl:for-each>
  </xsl:template>

  <!-- key for files -->
  <xsl:key name="filekey" match="file" use="."/>

  <!--
   !  Template for obj targets
   !-->
  <xsl:template name="objs">
# Object targets
# WARNING: this section is replaced entirely in the sync process
#------------------------------------------------------------------------------

<xsl:for-each select="/workspace/projects/project">
# <xsl:value-of select="@name"/><xsl:text>
</xsl:text>
  <xsl:for-each select="files/file">
    <!-- test whether not already created -->
    <xsl:if test="generate-id(.) = generate-id(key('filekey', .)[1])">
      <!-- only export .cpp files -->
      <xsl:if test="contains(., '.cpp')">
        <xsl:variable name="bn"><xsl:value-of select="func:basename(.)" /></xsl:variable>
          <xsl:text>obj </xsl:text><xsl:value-of select="$bn"/> : <xsl:value-of select="."/><xsl:text> ;
</xsl:text>
      </xsl:if>
    </xsl:if>
  </xsl:for-each>
</xsl:for-each><xsl:text>
</xsl:text>
  </xsl:template>


  <!--
   !  Template for dependencies
   !-->
  <xsl:template match="dependencies">
    # dependencies <xsl:text></xsl:text>
    <xsl:for-each select="dep">
    &lt;<xsl:value-of select="@type"/>&gt;<xsl:text></xsl:text>
      <!-- path? -->
      <xsl:if test=". != ''">
        <xsl:value-of select="."/><xsl:text> </xsl:text>
      </xsl:if>
      <!-- name -->
      <xsl:value-of select="@name"/>
    </xsl:for-each>
  </xsl:template>

</xsl:stylesheet>
