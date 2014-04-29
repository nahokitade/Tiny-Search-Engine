#!/bin/bash

crawlerFile=crawlerTestlog.`date +"%a_%b_%d_%T_%Y"`
directoryName=WebPageDirectory`date +"%a_%b_%d_%T_%Y"`

touch $crawlerFile
mkdir $directoryName

printf "crawler run with no arguments. Should give an usage error. Verify: \n" > $crawlerFile

crawler >> $crawlerFile 2>&1

printf "\n\n" >> $crawlerFile

printf "crawler run with a link that does not have the right prefix. Should give an usage error. Verify: \n" >> $crawlerFile

crawler http://www.header-not-right.cs.dartmouth.edu/~cs50/tse/ ./this_location_does_not_exist 1 >> $crawlerFile 2>&1

printf "\n\n" >> $crawlerFile

printf "crawler run with a dead link. Should give an usage error. Verify: \n" >> $crawlerFile

crawler http://old-www.cs.dartmouth.edu/~cs50/tse/deadlink.html ./$directoryName 1 >> $crawlerFile 2>&1

printf "\n\n" >> $crawlerFile

printf "crawler run with a directory that does not exist. Should give an usage error. Verify: \n" >> $crawlerFile

crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./this_location_does_not_exist 1 >> $crawlerFile 2>&1

printf "\n\n" >> $crawlerFile

printf "crawler run with an existing file rather than directory. Should give an usage error. Verify: \n" >> $crawlerFile

crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./crawler.c 1 >> $crawlerFile 2>&1

printf "\n\n" >> $crawlerFile

printf "crawler run with negative crawl depth. Should give an usage error. Verify: \n" >> $crawlerFile

crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./$directoryName -1 >> $crawlerFile 2>&1

printf "\n\n" >> $crawlerFile

printf "crawler run with too large crawl depth. Should give an usage error. Verify: \n" >> $crawlerFile

crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./$directoryName 20 >> $crawlerFile 2>&1

printf "\n\n" >> $crawlerFile

printf "crawler run with non int crawl depth. Should give an usage error. Verify: \n" >> $crawlerFile

crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./$directoryName kjgbvj >> $crawlerFile 2>&1

printf "\n\n" >> $crawlerFile

crawler http://old-www.cs.dartmouth.edu/~cs50/tse/wiki/Computer_science.html ./$directoryName 0

printf "The number of pages in depth 0 should be 1. Verify: " >> $crawlerFile

cd $directoryName

page_number=`ls | xargs -n1 head -n1 | sort | wc -l`

cd ..

printf "$page_number " >> $crawlerFile

printf "\n\n" >> $crawlerFile

crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./$directoryName 1

printf "The number of pages in depth 1 should be 7. Verify: " >> $crawlerFile

cd $directoryName

page_number=`ls | xargs -n1 head -n1 | sort | wc -l`
rm -f *

cd ..

printf "$page_number " >> $crawlerFile

printf "\n\n" >> $crawlerFile

crawler http://old-www.cs.dartmouth.edu/~cs50/tse/wiki/Computer_science.html ./$directoryName 2

printf "The number of pages in depth 2 should be 931. Verify: " >> $crawlerFile

cd $directoryName

page_number=`ls | xargs -n1 head -n1 | sort | wc -l` 
rm -f *

cd ..

printf "$page_number " >> $crawlerFile

printf "\n\n" >> $crawlerFile

crawler http://old-www.cs.dartmouth.edu/~cs50/tse/wiki/Computer_science.html ./$directoryName 3

printf "The number of pages in depth 3 should be 2031. Verify: " >> $crawlerFile

cd $directoryName

page_number=`ls | xargs -n1 head -n1 | sort | wc -l`
rm -f *

cd ..

printf "$page_number " >> $crawlerFile

rmdir $directoryName


