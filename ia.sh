#!/bin/bash

command=( "Forward" "Left" "Right" "Look" "Inventory" "Broadcast caca"
        "Connect_nbr" "Fork" "Eject" "Take Linemate" "Take Deraumere" "Take Sibur"
        "Take Mendiane" "Take Phiras" "Take Thystame" "Take Food" "Take caca"
        "Set Linemate" "Set Deraumere" "Set Sibur" "Set Mendiane" "Set Phiras"
        "Set Thystame" "Set Food" "Set caca" "Incantation" "caca" "Take Food"
         "Take Food" "Take Food" "Take Food" "Take Food" "Take Food" "Take Food")

if [ $# -lt 3 ]
then
    echo "USAGE : $0 <command_nbr> <team_to_join> <file_name>"
    exit 1;
fi

echo $2 > $3
for ((i=0;i<$1;++i)); do
    echo ${command[$(( ( RANDOM % 34 ) ))]} >> $3
done
