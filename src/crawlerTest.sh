#!/bin/bash


echo -e `crawler` | cat > crawler_test_file 2>&1

echo -e `crawler http://www.header-not-right.cs.dartmouth.edu/~cs50/tse/ ./this_location_does_not_exist 1` | cat >> crawler_test_file 2>&1

echo -e `crawler http://old-www.cs.dartmouth.edu/~cs50/tse/deadlink.html ./WebPageDir 1` | cat >> crawler_test_file 2>&1

echo -e `crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./this_location_does_not_exist 1` | cat >> crawler_test_file 2>&1

echo -e `crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./crawlerPages.log 1` | cat >> crawler_test_file 2>&1

echo -e `crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./WebPageDir -1` | cat >> crawler_test_file 2>&1

echo -e `crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./WebPageDir 20` | cat >> crawler_test_file 2>&1

echo -e `crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./WebPageDir kjgbvj` | cat >> crawler_test_file 2>&1

crawler http://old-www.cs.dartmouth.edu/~cs50/tse/wiki/Computer_science.html ./WebPageDir 2

printf("The number of pages in depth 2 should be 931. Verify: ") >> crawler_test_file

ls | xargs -n1 head -n1 | sort | wc -l | cat >> crawler_test_file

