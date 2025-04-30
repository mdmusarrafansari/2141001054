#!/bin/bash

file="fruits.txt"
search_word="apple"

grep "$search_word" "$file" | sort
