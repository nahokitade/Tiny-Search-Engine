#!/bin/bash

crawlerFile=crawlerTestlog.`date +"%a_%b_%d_%T_%Y"`

touch $crawlerFile

crawler > $crawlerFile 2>&1

crawler http://www.header-not-right.cs.dartmouth.edu/~cs50/tse/ ./this_location_does_not_exist 1 >> $crawlerFile 2>&1

printf "\n\n" >> $crawlerFile

crawler http://old-www.cs.dartmouth.edu/~cs50/tse/deadlink.html ./WebPageDir 1 >> $crawlerFile 2>&1

printf "\n\n" >> $crawlerFile

crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./this_location_does_not_exist 1 >> $crawlerFile 2>&1

printf "\n\n" >> $crawlerFile

crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./crawlerPages.log 1 >> $crawlerFile 2>&1

printf "\n\n" >> $crawlerFile

crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./WebPageDir -1 >> $crawlerFile 2>&1

printf "\n\n" >> $crawlerFile

crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./WebPageDir 20 >> $crawlerFile 2>&1

printf "\n\n" >> $crawlerFile

crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./WebPageDir kjgbvj >> $crawlerFile 2>&1

printf "\n\n" >> $crawlerFile

mkdir WebPageDirectory0

crawler http://old-www.cs.dartmouth.edu/~cs50/tse/wiki/Computer_science.html ./WebPageDirectory0 0

printf "The number of pages in depth 0 should be 1. Verify: " >> $crawlerFile

cd WebPageDirectory0

page_number=`ls | xargs -n1 head -n1 | sort | wc -l`

cd ..

printf "$page_number " >> $crawlerFile

printf "\n\n" >> $crawlerFile

mkdir WebPageDirectory1

crawler http://old-www.cs.dartmouth.edu/~cs50/tse/wiki/Computer_science.html ./WebPageDirectory1 1

printf "The number of pages in depth 1 should be 7. Verify: " >> $crawlerFile

cd WebPageDirectory1

page_number=`ls | xargs -n1 head -n1 | sort | wc -l`

cd ..

mkdir WebPageDirectory2

printf "$page_number " >> $crawlerFile

printf "\n\n" >> $crawlerFile


crawler http://old-www.cs.dartmouth.edu/~cs50/tse/wiki/Computer_science.html ./WebPageDirectory2 2

printf "The number of pages in depth 2 should be 931. Verify: " >> $crawlerFile

cd WebPageDirectory2

page_number=`ls | xargs -n1 head -n1 | sort | wc -l` 

cd ..

printf "$page_number " >> $crawlerFile

printf "\n\n" >> $crawlerFile

mkdir WebPageDirectory3

crawler http://old-www.cs.dartmouth.edu/~cs50/tse/wiki/Computer_science.html ./WebPageDirectory3 3

printf "The number of pages in depth 3 should be 2031. Verify: " >> $crawlerFile

cd WebPageDirectory3

page_number=`ls | xargs -n1 head -n1 | sort | wc -l`

cd ..

printf "$page_number " >> $crawlerFile

rm -rf WebPageDirectory0 WebPageDirectory1 WebPageDirectory2 WebPageDirectory3


