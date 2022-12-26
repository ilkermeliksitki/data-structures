#!/bin/bash

gcc -g -pipe -O0 -std=c11 ../../../week-1/tree_height.c -lm &&
for i in {01..24}
do
    result=$(cat cases/$i | ./a.out)
    test=$(cat cases/$i.a)
    # make if else and beautify
    if [ "$result" != "$test" ]
    then
        echo the case $i failed.
        echo $(cat cases/$i)
        echo your result =\> $result
        echo test result =\> $test
        printf "\n"
        break
    else
        echo passed $i
    fi
done
echo All test passed.
