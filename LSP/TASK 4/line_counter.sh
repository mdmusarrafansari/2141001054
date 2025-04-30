#!/bin/bash

# Function to count lines
count_lines() {
    local file=$1
    local lines=$(wc -l < "$file")
    echo "$file has $lines lines"
}

# List of files
files=("file1.txt" "file2.txt" "file3.txt")

# Loop through files
for file in "${files[@]}"; do
    if [ -f "$file" ]; then
        count_lines "$file"
    else
        echo "$file does not exist"
    fi
done
