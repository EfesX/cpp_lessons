#!/bin/bash

x=`cat ipfilter.tsv | build/ipfilter | md5sum`

echo $x

if [ "$x" == "24e7a7b2270daee89c64d3ca5fb3da1a" ]; then
    echo "OK" 
    exit 0
fi
echo "NOT OK"
exit 1
