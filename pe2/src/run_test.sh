#!/usr/bin/env bash
for i in test/test_*.txt; do
    echo "$i:"
    ./compilers-pe2 < "$i"
    wc < "$i"
    echo ""
done
