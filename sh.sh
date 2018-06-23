#!/bin/bash

if [ $# -lt 3 ]
then
    echo "USAGE : $0 <file_name> <client_nbr> <port>"
    exit 1;
fi

for ((i=0;i<$2;++i)); do
    cat $1 | nc -N -i 1 $4 $3 > /dev/null &
done
