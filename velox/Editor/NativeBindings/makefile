JAVASRC=../SourceV3d/de/velox
CPPSRC=GlueCode
JAVAPACKAGE=de.velox
DLLDEST=..
BUILDDIR=../../Local/Build/bjam/msvc/debug

all : swig cppfiles 

swig : TestLib.cpp TestLib.i
	mkdir -p $(CPPSRC)
	mkdir -p $(JAVASRC)
	swig -c++ -java -package $(JAVAPACKAGE) -outdir $(JAVASRC) -o $(CPPSRC)/TestLibSWIG.cpp TestLib.i
#	mkdir -p $(JAVASRC)/property
#	swig -c++ -java -package $(JAVAPACKAGE).property -outdir $(JAVASRC)/property -o $(CPPSRC)/PropertySWIG.cpp Property.i

cppfiles : *.h *.cpp
	bjam --v2
	cp $(BUILDDIR)/*.dll $(DLLDEST)
	cp $(BUILDDIR)/*.dll $(DLLDEST)/EclipsePlugin
#	cp ${BUILDDIR}/*.dll $(DLLDEST)/Constructor

cleanswig :
	rm -rdf $(JAVASRC)/*
	
#javafiles : *.java
#	mkdir -p $(JAVABIN)
#	javac -sourcepath $(JAVASRC) -d $(JAVABIN) *.java
#	cd $(JAVASRC); javac -d $(JAVABIN) *.java

