JAVASRC=../SourceV3d/de/velox
CPPSRC=GlueCode
JAVAPACKAGE=de.velox
DLLDEST=..
BUILDDIR=../../Local/Build/bjam2/msvc/debug

all : swig cppfiles 

swig : TestLib.cpp TestLib.i
	mkdir -p $(CPPSRC)
	mkdir -p $(JAVASRC)
	swig -c++ -java -package $(JAVAPACKAGE) -outdir $(JAVASRC) -o $(CPPSRC)/TestLibSWIG.cpp TestLib.i > swigbuild.log
	echo Finished swig
#	mkdir -p $(JAVASRC)/property
#	swig -c++ -java -package $(JAVAPACKAGE).property -outdir $(JAVASRC)/property -o $(CPPSRC)/PropertySWIG.cpp Property.i

cppfiles : *.h *.cpp
	bjam2.bat
	cp $(BUILDDIR)/*.dll $(DLLDEST)
	cp $(BUILDDIR)/*.dll $(DLLDEST)/EclipsePlugin
	echo
	echo Successful compilation on `date`

cleanswig :
	rm -rdf $(JAVASRC)/*
	
#javafiles : *.java
#	mkdir -p $(JAVABIN)
#	javac -sourcepath $(JAVASRC) -d $(JAVABIN) *.java
#	cd $(JAVASRC); javac -d $(JAVABIN) *.java

