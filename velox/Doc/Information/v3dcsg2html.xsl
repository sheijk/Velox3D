<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet 
	version="1.0" 
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:fo="http://www.w3.org/1999/XSL/Format"
	xmlns:v3d="http://www.sechsta-sinn.de/velox"
>

	<!-- Root Element matchen (= alle Sektionen generieren) -->
	<xsl:template match="/">
		<html>
			<body>
				<h1><xsl:value-of select="child::guidelines/title"/></h1>
				<p>
					<xsl:apply-templates select="guidelines/version"/>
					<xsl:apply-templates select="guidelines/author"/>
					<h2>Overview</h2>
					<p>Links fehlen leider noch</p>
					<xsl:apply-templates select="guidelines/section" mode="ref"/>
					<h2>Content</h2>
					<xsl:apply-templates select="guidelines/section" mode="complete"/>
				</p>
			</body>
		</html>
	</xsl:template>
	
	<xsl:template match="version">
		Version <i>#<xsl:value-of select="text()"/></i><br />
	</xsl:template>
	
	<xsl:template match="author">
		by <i><xsl:value-of select="text()"/></i><br />
	</xsl:template>

	<!-- Alle Coding style guidelines mit kompletter Beschreibung erzeugen -->
	<xsl:template match="guidelines/section" mode="complete">
		<h3>Section <xsl:value-of select="@name"/></h3>
		<xsl:for-each select="rule">
			<h4>Rule</h4>
			<xsl:value-of select="text()"/>
			<xsl:apply-templates select="./*"/>
		</xsl:for-each>
	</xsl:template>
	
	<!-- Inhaltsverzeichnis der Sektionen generieren -->
	<xsl:template match="guidelines/section" mode="ref">
		<!-- a href="about::blank"><xsl:value-of select="@name"/></a><br / -->
		<xsl:value-of select="@name" /> <br />
	</xsl:template>
	
	<xsl:template match="code">
		<p>
			<i>Sample Code</i><br />
			<xsl:value-of select="text()"/>
		</p>
	</xsl:template>
	<xsl:template match="reason">
		<p>
			<i>Reason</i><br />
			<xsl:value-of select="."/>
		</p>		
	</xsl:template>
</xsl:stylesheet>
