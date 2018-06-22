#!/bin/bash

if [ $# -lt 3 ]
then
    echo "USAGE : $0 <file_name> <client_nbr> <port>"
    exit 1;
fi

for ((i=0;i<$2;++i)); do
    cat $1 | nc -i 1 0 $3 > /dev/null &
done
