#!/bin/bash

src=$1
bdir=`dirname $1`
outdir=objs/$bdir
out=`basename $src`
out=${out%%.cc}
out=${out%%.cpp}
out=${out%%.cxx}
out=${out%%.C}

mkdir -p $outdir

g++ -g -Wall "$src" -o "$outdir/$out"

