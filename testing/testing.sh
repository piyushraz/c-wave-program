#!/bin/bash

if [ "$#" -ne 5 ]; then
  echo "Usage: $0 delay volume fileinput fileoutput filecompare"
  exit 1
fi

delay="$1"
volume="$2"
fileinput="$3"
fileoutput="$4"
filecompare="$5"

echo "Running addecho with delay: $delay, volume: $volume, input: $fileinput, output: $fileoutput"
./addecho -d "$delay" -v "$volume" "$fileinput" "$fileoutput"

# Check if addecho was successful
if [ $? -ne 0 ]; then
  echo "addecho command failed."
  exit 1
fi

COMPARE_SCRIPT="./compare_wav_files.sh"
echo "Comparing $filecompare with $fileoutput"
bash "$COMPARE_SCRIPT" "$filecompare" "$fileoutput"


# gcc -Wall -Werror -o addecho addecho.c