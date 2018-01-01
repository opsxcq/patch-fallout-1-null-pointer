#!/bin/bash

### Generate C source for .patch files

if [ -z "$1" ]
then
    echo '[-] Please inform a patch file to be transformed'
    exit -1
fi

for line in $(cat $1 | grep ':')
do
    byteOffset=$(echo $line | cut -d ':' -f 1)
    byteValue=$(echo $line | cut -d '>' -f 2 | tr -d '\n')
    echo '  fseek(gameFile, 0x'${byteOffset}', SEEK_SET);'
    echo  "  fwrite((void *) \"\x$byteValue\", 1, 1, gameFile);"
done
