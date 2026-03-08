#!/bin/bash

# file="data.txt"

file="th_grid.txt"

# delay=0.5
delay=0.1

while true; do
awk -v d="$delay" '

/START/ {ln=1}

{
    printf "%3d | %s\n", ln, $0
    ln++
}

/END/ {
    system("sleep " d)
    system("clear")
}

' "$file"
done