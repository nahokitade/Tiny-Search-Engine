#!/bin/bash
#
# Test Overview
# 1) Check for all the bad argument cases that should print an error.
# 2) We run query on multiple different query inputs, and test the 
# number of files it produces to the expected number of files.
# 
# Special consideration: The test results should be used wth command cat
# on a linux machine for full coloring effect of the query results. 

DATA_PATH="/net/class/cs50/tse/crawler"     # where the crawler data is
INDEX_FILE="~cs50/tse/indexer/cs_lvl3.dat"  # name of initial output file

queryFile=queryTestlog.`date +"%a_%b_%d_%T_%Y"`

touch $queryFile

startTime=`date +"%T on %m/%d/%Y"`
OS=`uname`

# starting and general info
printf "Starting Time: $startTime\nHost name of run: $HOSTNAME\nOperating System of run: $OS\n\n" >> $queryFile

# make correctly
printf "Starting cleaning and making...\n" >> $queryFile

make clean >> $queryFile 2>&1
make query >> $queryFile 2>&1

if [ $? -eq 0 ]; then # check return value of make
        printf "\nMake ran properly without errors.\n\n" >> $queryFile
else # failed make
        printf "\nMake did not successfully make indexer... exiting.\n\n" >> $queryFile
        endTime=`date +"%T on %m/%d/%Y"`
        printf "Ending Time: $endTime\n" >> $queryFile
        exit 1
fi

# start of errror arguments and inputs testing 

printf "With no arguments, error message should show to inform user of usage.\n" >> $queryFile

./query >> $queryFile 2>&1

printf "\n\n" >> $queryFile

printf "With too many args, error message should show to inform user of usage.\n" >> $queryFile
./query ~cs50/tse/indexer/cs_lvl3.dat ~cs50/tse/crawler/lvl3 tooManyArgs >> $queryFile 2>&1

printf "\n\n" >> $queryFile

printf "With invalid directory argument, query will inform that the given directory is not a directory.\n" >> $queryFile
./query ~cs50/tse/indexer/cs_lvl3.dat ~cs50/tse/crawler/lvl3/dirDontExist >> $queryFile 2>&1

printf "\n\n" >> $queryFile

printf "With invalid indexer file argument, the query will inform that the givem file is not valid.\n" >> $queryFile
./query ~cs50/tse/indexer/cs_lvl3DontExist.dat ~cs50/tse/crawler/lvl3 >> $queryFile 2>&1

printf "\n\n" >> $queryFile

printf "With query of more than 1000 characters, query will inform the user to give a query of less than 1000 characters.\n" >> $queryFile
cat twoThousandChars.txt | ./query ~cs50/tse/indexer/cs_lvl3.dat ~cs50/tse/crawler/lvl3 >> $queryFile 2>&1

printf "\n\n" >> $queryFile

# starting valid input tests. (tests should be self explanatory looking at printf statements.)
printf "\nStart of valid command inputs. The expected number of files is at the bottom of each execution of test for easier comparison.\n" >> $queryFile

printf "Query: cat AND dog (testing AND condition)\n" >> $queryFile
echo "cat AND dog" | ./query ~cs50/tse/indexer/cs_lvl3.dat ~cs50/tse/crawler/lvl3 >> $queryFile 2>&1
printf "\nShould have found 12 files." >> $queryFile

printf "\n\n" >> $queryFile

printf "Query: CAT AND DOG (testing for lowercasing)\n" >> $queryFile
echo "CAT AND DOG" | ./query ~cs50/tse/indexer/cs_lvl3.dat ~cs50/tse/crawler/lvl3 >> $queryFile 2>&1
printf "\nShould have found 12 files." >> $queryFile

printf "\n\n" >> $queryFile

printf "Query: or dog (testing space condition which should AND, and a non-existing first word)\n" >> $queryFile
echo "or dog" | ./query ~cs50/tse/indexer/cs_lvl3.dat ~cs50/tse/crawler/lvl3 >> $queryFile 2>&1
printf "\nShould have found 0 files." >> $queryFile

printf "\n\n" >> $queryFile

printf "Query: or OR dog (non-existing first word ORed with a valid word)\n" >> $queryFile
echo "or OR dog" | ./query ~cs50/tse/indexer/cs_lvl3.dat ~cs50/tse/crawler/lvl3 >> $queryFile 2>&1
printf "\nShould have found 55 files." >> $queryFile

printf "\n\n" >> $queryFile

printf "Query: cat OR dog (testing OR condition)\n" >> $queryFile
echo "cat OR dog" | ./query ~cs50/tse/indexer/cs_lvl3.dat ~cs50/tse/crawler/lvl3 >> $queryFile 2>&1
printf "\nShould have found 257 files." >> $queryFile

printf "\n\n" >> $queryFile

printf "Query: cat and dog  (testing space condition which should AND, and lowercase operators)\n" >> $queryFile
echo "cat and dog" | ./query ~cs50/tse/indexer/cs_lvl3.dat ~cs50/tse/crawler/lvl3 >> $queryFile 2>&1
printf "\nShould have found 12 files." >> $queryFile

printf "\n\n" >> $queryFile

printf "Query: cat dog (testing space condition which should AND)\n" >> $queryFile
echo "cat dog" | ./query ~cs50/tse/indexer/cs_lvl3.dat ~cs50/tse/crawler/lvl3 >> $queryFile 2>&1
printf "\nShould have found 12 files." >> $queryFile

printf "\n\n" >> $queryFile

printf "Query: cat AND dog OR head AND tail (testing longer cases with combination of OR and AND)\n" >> $queryFile
echo "cat AND dog OR head AND tail" | ./query ~cs50/tse/indexer/cs_lvl3.dat ~cs50/tse/crawler/lvl3 >> $queryFile 2>&1
printf "\nShould have found 178 files." >> $queryFile

printf "\n\n" >> $queryFile

printf "Query: \\n (testing no input)\n" >> $queryFile
echo "\n" | ./query ~cs50/tse/indexer/cs_lvl3.dat ~cs50/tse/crawler/lvl3 >> $queryFile 2>&1
printf "\nShould have found 0 files." >> $queryFile

printf "\n\n" >> $queryFile

printf "Query: ksvjsngvaen (testing non sense input)\n" >> $queryFile
echo "ksvjsngvaen" | ./query ~cs50/tse/indexer/cs_lvl3.dat ~cs50/tse/crawler/lvl3 >> $queryFile 2>&1
printf "\nShould have found 0 files." >> $queryFile

printf "\n\n" >> $queryFile


# clean the files used, and exit.
printf "cleaning the made files.\n" >> $queryFile
make clean >> $queryFile 2>&1

printf "\n" >> $queryFile

endTime=`date +"%T on %m/%d/%Y"`
printf "Ending Time: $endTime\n" >> $queryFile

exit 0

