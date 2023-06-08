#!/bin/bash

# compile the C code with debugging symbols
gcc -g -pipe -O0 -std=c11 ../../../week-6/tree_traversals.c -lm -o a.out

# define an array of test case numbers
test_cases=("01" "02" "03")

# colors
RED='\033[0;31m'
RED_BOLD='\033[1;31m'
GREEN_BOLD='\033[1;32m'
NC='\033[0m'    # No Color

# iterate over the test case files
for i in "${test_cases[@]}"
do
    # execute the program using Valgrind and capture the output
    valgrind_output=$(valgrind --leak-check=full ./a.out < "cases/$i" 2>&1)

    # check if Valgrind reported any memory leaks
    if [[ "$valgrind_output" =~ "All heap blocks were freed -- no leaks are possible" ]]; then
        memory_leak_info="${GREEN_BOLD}without memory leak${NC}"
    else
        memory_leak_info="${RED_BOLD}with memory leak${NC}"
    fi

    # execute the program again and capture the program's output
    result=$(./a.out < "cases/$i")

    # read the expected output from the file
    expected=$(cat "cases/$i.a")

    # compare the result and the expected output
    # If there is a trailing space, it will appear as a red block character.
    if [ "$result" != "$expected" ]; then
        echo -e "Test case $i failed ${memory_leak_info}"
        echo "Input:"
        cat "cases/$i"
        echo -e "\nYour result:"
        echo -e "$result" | sed -E "s/[[:space:]]+$/$(printf "${RED}█${NC}")/"
        echo -e "\nExpected result:"
        echo -e "$expected" | sed -E "s/[[:space:]]+$/$(printf "${RED}█${NC}")/"
        echo
        exit 1
    else
        echo -e "Test case $i passed ${memory_leak_info}"
    fi
done

echo "All tests passed."

