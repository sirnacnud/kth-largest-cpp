kth-largest-cpp
===============

C++ solution to the kth largest element problem

### Problem
Given an unordered list of integers, find the *kth* largest elements in linear time, *O(n)*.

### Solution
The [median of medians](http://en.wikipedia.org/wiki/Median_of_medians) algorithm was implemented in order to guarantee the *kth* largest elements were found in linear time.

### Program
The supplied c++ program takes a file containing numbers, delimited by newline, and a number for the *kth* largest numbers to find.

### Example
Find the four largest numbers in the supplied sample file:
```
$ kth-largest-cpp sample 4
>> 22
>> 23
>> 24
>> 25
