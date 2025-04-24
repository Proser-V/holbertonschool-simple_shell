#!/bin/bash

# Variables
command="ls 
/bin/ls     
   ls 
ls
 ls     "
tmp_file="checker_tmp_file_$RANDOM"
shell_exec="./hsh"          # Your compiled shell executable
output_file="output.txt"

# Cleanup before starting
rm -f "$tmp_file" "$output_file"

# Create a temporary file (so we can check if it's listed)
touch "$tmp_file"

# Send the commands to your shell
echo "$command" | $shell_exec > "$output_file" 2>/dev/null

# Check how many times the temporary file is listed
nmatch=$(grep -c "$tmp_file" "$output_file")

# Result
if [ "$nmatch" -eq 5 ]; then
    echo "✅ Test passed: $nmatch/5 occurrences found"
    result=0
else
    echo "❌ Test failed: $nmatch/5 occurrences found"
    echo "---- Full Output ----"
    cat "$output_file"
    echo "----------------------"
    result=1
fi

# Cleanup
rm -f "$tmp_file" "$output_file"

exit $result