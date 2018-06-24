#!/bin/bash

for ((i=0;i<$1;++i)); do
    ./zappy_ai -p 8888 -n caca -h $2 &
done
