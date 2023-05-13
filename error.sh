#!/bin/bash

file="$1"

gcc -o /dev/null "$file" 2> temp.txt

num_errors=$(grep -c "error" temp.txt)
num_warnings=$(grep -c "warning" temp.txt)

if [ "$num_errors" -eq 0 ] && [ "$num_warnings" -eq 0 ]; then
    score=10
elif [ "$num_errors" -ge 1 ]; then
    score=1
elif [ "$num_warnings" -gt 10 ]; then
    score=2
else
    score=$(echo "2 + 8 * (10 - $num_warnings) / 10" | bc)
fi

echo "Errors: $num_errors"
echo "Warnings: $num_warnings"
echo "Score: $score"

rm temp.txt

echo "$score"
