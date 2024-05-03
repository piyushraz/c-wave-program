#!/bin/bash

# Check if two arguments were passed
if [ "$#" -ne 2 ]; then
  echo "Usage: $0 file1.wav file2.wav"
  exit 1
fi

# Assign arguments to variables
file1="$1"
file2="$2"

# Compare the two files
cmp -s "$file1" "$file2"

# Get the exit status of the cmp command
status=$?

echo " "

# Check the status
if [ $status -eq 0 ]; then
  echo -e "\033[1;32mFiles are the same, no differences found.\033[0m"
elif [ $status -eq 1 ]; then
  echo -e "\033[1;31mFiles are different.\033[0m"
else
  echo "An error occurred while comparing files."
fi

echo -e "\033[1;34m-----------------------------------------------------------------------------------------------------------\033[0m"