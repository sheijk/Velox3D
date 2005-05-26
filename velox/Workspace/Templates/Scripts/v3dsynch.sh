#!/bin/bash

#------------------------------------------------------------------------------
# mbuild base script
#------------------------------------------------------------------------------

# config
#------------------------------------------------------------------------------

# string to prepend the RelativePath in .vcproj Files
VC_PREF='../../';

# paths
MB_SCRIPT_PATH=$(cd $(dirname $0); pwd)/v3dsynch;

# executable names
exe_tidy="xmllint --format -";
exe_xsltproc="xsltproc";        # xslt processor

# stylesheets
xslt_vc2mb="sync_vc2mb.xsl";
xslt_mb2vc="sync_mb2vc.xsl";
xslt_mb2bj="sync_mb2bj.xsl";
xslt_mb2bj_obj="sync_mb2bj_obj.xsl";
xslt_bjam="gen_bjam.xsl";
xslt_vcproj="gen_vcproj.xsl";
xslt_projects="extract_projects.xsl";
xslt_type="extract_type.xsl";
xslt_insertprj="insertproject.xsl";

###############################################################################
# helper functions
###############################################################################

# echo usage information
#------------------------------------------------------------------------------
function echoUsage {
    echo "USAGE: mbuild.sh <command> <file1> ... <filen>"
    echo "      valid commands: vc2mb <vcproj> <mbuild> - sync .vcproj with mbuild file"
    echo "                      mb2vc <mbuild> [<vcproj>] - sync mbuild file with .vcproj"
    echo "                      mb2bj <mbuild> <bjam> - sync mbuild file with bjam file"
    echo "                       bjam <mbuild> <bjam> - generate bjam file"
    echo "                     vcproj <mbuild> - generate .vcproj files into current directories"
}

# check for DOCTYPE declaration
# param mbfile
#------------------------------------------------------------------------------
function dtcheck {
    dt=`grep DOCTYPE "$1"` 
    if [ -z "$dt" ]; then 
        echo "No DOCTYPE declaration found, please make sure $1 contains one";
        exit 1 
    fi
}

# copy a vcproj template
# param: Project name
# param: mbuild file
#------------------------------------------------------------------------------

function copyVCTemplate {
    # filename
    fn=$1.vcproj
    echo "generating $fn ..."
    
    # extract type
    tp=`$exe_xsltproc --stringparam __project $1 "$MB_SCRIPT_PATH"/$xslt_type $2 | tr -d [:space:] `
    
    # copy template
    template="$tp.Template.vcproj";
    cp "$MB_SCRIPT_PATH"/$template $fn

    # replace name
    sed -e"s/%%name%%/$1/g" $fn > $fn.new
    mv $fn.new $fn
    # replace projectid
    sed -e"s/%%projectid%%/`date +%Y%m%d-0000-0000-0000-000%N`/g" $fn > $fn.new
    mv $fn.new $fn
    # replace relpath
    sed -e"s/%%relpath%%/..\/../g" $fn > $fn.new # TODO: set relpath more intelligently
    mv $fn.new $fn
        
}

# check whether a project exists in an mbuild file, abort if not
# param: projectname
# param: mbfile 
#------------------------------------------------------------------------------
function checkProject {
    # check whether a project of name $bn exists
    foundproject="0";
    # extract projects
    ps=`$exe_xsltproc "$MB_SCRIPT_PATH"/$xslt_projects $2`
    for i in $ps; do
        if [ "$1" == "$i" ]; then
            foundproject="1";
        fi;
    done

    return $foundproject;

    if [ "0" -eq "$foundproject" ]; then
        return 0;
    fi

    return 1;

}


###############################################################################
# core functions
###############################################################################

# sync .vcproj to mbuild.xml
# param: vcfile - .vcproj file to convert from
# param: mbfile - mbuild file to sync to
# return: bool indicating success
#------------------------------------------------------------------------------
function syncvc2mb {
    # TODO: perform some sanity checks on files
    dtcheck $2;
    # extract Doctype
    dt=`grep DOCTYPE "$2"`
    # get basename
    bn=`basename "$1" .vcproj`
    #check project
    if checkProject $bn $2; then
        echo "no project named $bn found in $2, creating it";
        # TODO: insert project
        $exe_xsltproc --stringparam __vcproj $bn "$MB_SCRIPT_PATH"/$xslt_insertprj $2 | $exe_tidy > $2.new
        mv $2.new $2
        echo "WARNING! inserted new project $bn into $2, please check type!"
    fi
    # execute xslt processor
    $exe_xsltproc --stringparam __prefix "$VC_PREF" --stringparam __vcprojfile "`pwd`"/$1 --stringparam __vcproj $bn "$MB_SCRIPT_PATH"/$xslt_vc2mb $2 | $exe_tidy > $2.new
    mv $2.new $2

    return 1
}

function vc2mb {
    # check for both arguments
    if [ -z $1 ]; then 
        echo "too few arguments "; 
        return 0 
    fi
    # check for valid files
    if [ ! -f $1 ]; then 
        echo "Not a valid file: $1";
        return 0
    fi
    
    if [[ ! -f $2 && -z $2 ]]; then 
        echo "Not a valid file: $2 - syncing all .vcproj files in current dir...";
        fs=`find ./ -maxdepth 1  -name \*.vcproj`
        for i in $fs; do
            echo "syncing $i";
            syncvc2mb $i $1
        done
        return 0
    else
        syncvc2mb $1 $2
    fi
}

# sync mbuild.xml to .vcproj
# param: mbfile - mbuild file to sync to
# param: vcfile - .vcproj file to convert from
# return: bool indicating success
#------------------------------------------------------------------------------
function syncmb2vc {
    # get basename
    bn=`basename "$2" .vcproj`
    # check whether project exitst
    if checkProject $bn $1; then
        echo "no project named $bn found in $1, aborting"; 
        exit;
    fi

    fn=$bn.vcproj
        
    if [ ! -f $fn ]; then 
        echo "Not a valid file: $fn, creating it...";
        copyVCTemplate $bn $1
    fi
    # TODO: perform some sanity checks on files
    dtcheck $1;

    # execute xslt processor
    $exe_xsltproc --stringparam __prefix "$VC_PREF" --stringparam __mbfile "`pwd`"/$1 --stringparam __vcproj $bn "$MB_SCRIPT_PATH"/$xslt_mb2vc $fn | $exe_tidy > $fn.new 
    # swap files
    mv $fn.new $fn
    return 1
}

function mb2vc {
    # check for both arguments
    if [ -z $1 ]; then 
        echo "too few arguments $1 $2"; 
        return 0 
    fi
    # check for valid files
    if [ ! -f $1 ]; then 
        echo "Not a valid file: $1";
        return 0
    fi
    # check whether vcfile is given
    if [ -z $2 ]; then
        # no second argument, sync all
        echo "no second argument, syncing all";
        # extract projects
        ps=`$exe_xsltproc "$MB_SCRIPT_PATH"/$xslt_projects $1`;
        for i in $ps; do
            echo "-> syncing with $i ..."
            syncmb2vc $1 $i
        done;
    else
        # file or project given, sync just this one
        syncmb2vc $1 $2
    fi
}

# sync mbuild.xml to bjam Jamfile
# param: mbfile - mbuild file to sync to
# param: bjfile - .vcproj file to convert from
# return: bool indicating success
#------------------------------------------------------------------------------
function mb2bj {
    # check for both arguments
    if [ -z $2 ]; then 
        echo "too few arguments $1 $2"; 
        return 0 
    fi
    # check for valid files
    if [ ! -f $1 ]; then 
        echo "Not a valid file: $1";
        return 0
    fi
    if [ ! -f $2 ]; then 
        echo "Not a valid file: $2";
        return 0
    fi
    # TODO: perform some sanity checks on files
    dtcheck $1;
    # extract projects
    ps=`$exe_xsltproc "$MB_SCRIPT_PATH"/$xslt_projects $1`
    # create files for every project
    for i in $ps; do
        echo "generating files for $i ..."
        $exe_xsltproc --stringparam project $i "$MB_SCRIPT_PATH"/$xslt_mb2bj $1 | perl "$MB_SCRIPT_PATH"/insert_bjam.pl $2 $i 
    done
    echo "regenerating object targets"
    # rip object targets from File
    sed -e'/^# Object targets/,$d' $2 > $2.new
    # generate new object targets
    $exe_xsltproc "$MB_SCRIPT_PATH"/$xslt_mb2bj_obj $1 >> $2.new
    mv $2.new $2
     
    
    return 1
}

# generate bjam file from mbuild.xml
# param: mbfile - mbuild file to generate from
#------------------------------------------------------------------------------
function bjam {
    # check for arguments
    if [ -z $2 ]; then
        echo "too few arguments $1 $2";
        return 0
    fi
    # check for valid files
    if [ ! -f $1 ]; then 
        echo "Not a valid file: $1";
        return 0
    fi
    dtcheck $1;
    #execute xslt processor
    $exe_xsltproc "$MB_SCRIPT_PATH"/$xslt_bjam $1 > $2
}


# generate .vcproj files from mbuild.xml
# param: mbfile - mbuild file to generate from
#------------------------------------------------------------------------------
function vcproj {
    # check for arguments
    if [ -z $1 ]; then
        echo "too few arguments";
        return 0
    fi
    dtcheck $1;
    # extract projects
    ps=`$exe_xsltproc "$MB_SCRIPT_PATH"/$xslt_projects $1`
    # iterate over projects and generate .vcproj
    for i in $ps; do
        # copy template
        copyVCTemplate $i $1

        # import files
        echo "  -> importing files from $1"
        sh $0 mb2vc $1 $i.vcproj
        
    done
}


# check for task and usage
#------------------------------------------------------------------------------

case $1 in
    "vc2mb"         )
        vc2mb $2 $3
    ;;
    "mb2vc"         )
        mb2vc $2 $3 
    ;;
    "mb2bj"         )
        mb2bj $2 $3
    ;;
    "bjam"          )
        bjam $2 $3
    ;;
    "vcproj"        )
        vcproj $2
    ;;
    *               )
        echo "ERR: no validcommand given";
        echoUsage
    ;;
esac
    



