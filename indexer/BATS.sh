#!/bin/bash 
#
# Test Overview
# 1) Check for all the bad argument cases that should print an error. 
# 2) We index a directory, recorded it into a file (index.dat) and sort.
# Then we read index.dat to memory and write it back to see
# whether program can read in and write out index storage file correctly.
# The 

DATA_PATH="/net/class/cs50/tse/crawler"     # where the crawler data is
INDEX_FILE="index.dat"			    # name of initial output file
NEW_INDEX_FILE="new_index.dat"		    # name of second output file
counter=0				    # to increment through different level dirs

indexerFile=indexerTestlog.`date +"%a_%b_%d_%T_%Y"`

touch $indexerFile

startTime=`date +"%T on %m/%d/%Y"`
OS=`uname`

# starting and general info
printf "Starting Time: $startTime\nHost name of run: $HOSTNAME\nOperating System of run: $OS\n\n" >> $indexerFile

# make correctly
printf "Starting cleaning and making...\n" >> $indexerFile

make clean >> $indexerFile 2>&1
make indexer >> $indexerFile 2>&1

if [ $? -eq 0 ]; then # check return value of make
	printf "\nMake ran properly without errors.\n\n" >> $indexerFile
else # failed make
        printf "\nMake did not successfully make indexer... exiting.\n\n" >> $indexerFile
	endTime=`date +"%T on %m/%d/%Y"`
	printf "Ending Time: $endTime\n" >> $indexerFile
	exit 1
fi

# tests for invalid arguments. Tests are self explanatory
printf "With no arguments, error message should show to inform user of usage.\n" >> $indexerFile
./indexer >> $indexerFile 2>&1

printf "\n\n" >> $indexerFile

printf "With too few arguments, indexer will inform that the number of arguments must be 3 or 5.\n" >> $indexerFile

./indexer $DATA_PATH/lvl$counter/ >> $indexerFile 2>&1

printf "\n\n" >> $indexerFile

printf "With too many arguments, indexer will inform that the number of arguments must be 3 or 5.\n" >> $indexerFile

./indexer $DATA_PATH/lvl$counter/ $INDEX_FILE $INDEX_FILE $NEW_INDEX_FILE randomArg >> $indexerFile 2>&1

printf "\n\n" >> $indexerFile

printf "With invalid directory argument, indexer will inform that the given directory is not a directory.\n" >> $indexerFile

./indexer $DATA_PATH/lvl$counter/notRealDirectory $INDEX_FILE $INDEX_FILE $NEW_INDEX_FILE >> $indexerFile 2>&1

printf "\n\n" >> $indexerFile

touch $INDEX_FILE

chmod -w $INDEX_FILE

printf "With already existing file without write permission, indexer will inform that the indexer failed in the build or output of the file.\n" >> $indexerFile

./indexer $DATA_PATH/lvl$counter $INDEX_FILE $INDEX_FILE $NEW_INDEX_FILE >> $indexerFile 2>&1

printf "\n\n" >> $indexerFile

chmod +w $INDEX_FILE

# testing for correct output for the test run of indexer at different crawler level files (counter increments)
while [ $counter -le 3 ] 
do
	./indexer $DATA_PATH/lvl$counter/ $INDEX_FILE $INDEX_FILE $NEW_INDEX_FILE >> $indexerFile

	# use sort to order the index files to look at them else they remain unordered
	echo "Indexes have been built, read and rewritten correctly!" >> $indexerFile
	sort -o $INDEX_FILE $INDEX_FILE
	sort -o $NEW_INDEX_FILE $NEW_INDEX_FILE
	
	# compare the files to see that they are identical.
	diff -q -s $INDEX_FILE $NEW_INDEX_FILE > /dev/null
	if [ $? -eq 0 ]; then # check return value of diff
		echo "Index storage passed test at lvl$counter!" >> $indexerFile
	else # files are different
		echo "Index storage didn’t pass test at lvl$counter!" >> $indexerFile
	fi

	let counter=counter+1

	#clean up any files used
	rm -f $INDEX_FILE $NEW_INDEX_FILE

	printf "\n" >> $indexerFile
done

# clean the files used, and exit.
printf "cleaning the made files.\n" >> $indexerFile
make clean >> $indexerFile 2>&1

printf "\n" >> $indexerFile

endTime=`date +"%T on %m/%d/%Y"`
printf "Ending Time: $endTime\n" >> $indexerFile

exit 0

