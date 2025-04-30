#!/bin/bash

# Declare variables
str_var="Hello World"
int_var=10

# If-else statement
if [ $int_var -gt 5 ]; then
    echo "$str_var - The integer is greater than 5"
else
    echo "$str_var - The integer is 5 or less"
fi
