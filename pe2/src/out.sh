#!/usr/bin/env bash
rm output.txt
for i in test/test_*.txt; do
    { echo "$i":; ./compilers-pe2 < "$i"; echo ""; } >> output.txt
done
