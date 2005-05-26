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
   !  Template for workspace
   !-->
  <xsl:template match="workspace">
    <VisualStudioProject
      ProjectType="Visual C++"
      Version="7.10"
      ProjectGUID="{BB57F1C9-0039-40BC-8188-02F384F49029}"
      Keyword="Win32Proj"
    >
      <xsl:attribute name="Name"><xsl:value-of select="$__vcproj"/></xsl:attribute>
      <Platforms>
        <Platform Name="Win32"/>
      </Platforms>
      <xsl:apply-templates />
    </VisualStudioProject>
  </xsl:template>
 
  <!--
   !  Template for projects
   !-->
  <xsl:template match="project">
    <xsl:if test="@name = $__vcproj">
      <Files>
        <xsl:for-each select="files/file">
          <File>
            <xsl:attribute name="RelativePath"><xsl:value-of select="."/></xsl:attribute>
          </File>
        </xsl:for-each>
      </Files>
    </xsl:if>
  </xsl:template>


</xsl:stylesheet>
