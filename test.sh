#!/bin/bash

for ((i=0;i<$1;++i)); do
    ./zappy_ai -p 4242 -n mdr &
done
