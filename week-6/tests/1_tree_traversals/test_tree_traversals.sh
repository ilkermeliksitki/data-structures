#!/bin/bash

# Compile the C code
gcc -g -pipe -O0 -std=c11 ../../../week-6/tree_traversals.c -lm -o a.out

# Define an array of test case numbers
test_cases=("01" "02" "03")

# Define red color
RED='\033[0;31m'
NC='\033[0m'    # No Color

# Iterate over the test case files
for i in "${test_cases[@]}"
do
    # Execute the program and capture the output
    result=$(./a.out < "cases/$i")

    # Read the expected output from the file
    expected=$(cat "cases/$i.a")

    # Compare the result and the expected output
    # If there is a trailing space, it will appears as a red block character.
    if [ "$result" != "$expected" ]; then
        echo "Test case $i failed."
        echo "Input:"
        cat "cases/$i"
        echo -e "\nYour result:"
        echo -e "$result" | sed -E "s/[[:space:]]+$/$(printf "${RED}█${NC}")/"
        echo -e "\nExpected result:"
        echo -e "$expected" | sed -E "s/[[:space:]]+$/$(printf "${RED}█${NC}")/"
        echo
        exit 1
    else
        echo "Test case $i passed."
    fi
done

echo "All tests passed."

