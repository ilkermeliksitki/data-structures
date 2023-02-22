#!/bin/bash

gcc -g -pipe -O0 -std=c11 ../../../week-4/hash_substring.c -lm &&
for i in {01..04}
do
    result=$(cat cases/$i | ./a.out | xargs)
    test=$(cat cases/$i.a | xargs)
    if [ "$result" != "$test" ]; then
        echo the case $i failed.
        echo $(cat cases/$i)
        echo your result =\> $result
        echo test result =\> $test
        printf "\n"
        exit
    else
        echo passed $i
    fi
done
echo "All test passed."
