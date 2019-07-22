#!/bin/bash

[ ! -e "$1" ] && {
    echo -e "usage:\n$0 path/to/file-name.cxx"
    exit 1
}

src=$1
bdir=`dirname $1`
#outdir=objs/$bdir
outdir=objs #conform with vs code
out=`basename $src`
out=${out%%.cc}
out=${out%%.cpp}
out=${out%%.cxx}
out=${out%%.C}

mkdir -p $outdir

g++ -g -Wall "$src" -o "$outdir/$out"

