#!/bin/bash

gcc -g -pipe -O0 -std=c11 ../../../week-1/brackets_in_code.c -lm
for i in {01..54}
do
    result=$(cat cases/$i | ./a.out)
    test=$(cat cases/$i.a)
    #echo $result $test
    if [ "$result" != "$test" ]
    then
        echo the case $i failed.
        echo $(cat cases/$i)
    fi
done
