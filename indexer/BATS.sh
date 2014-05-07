#!/bin/bash 
make clean > /dev/null
make indexer > /dev/null

DATA_PATH="/net/class/cs50/tse/crawler"     #where the crawler data is
INDEX_FILE="index.dat"
NEW_INDEX_FILE="new_index.dat"
counter=0

# We index a directory, recorded it into a file (index.dat) and sort.
# Then we read index.dat to memory and write it back to see
# whether program can read in and write out index storage file correctly.

indexerFile=indexerTestlog.`date +"%a_%b_%d_%T_%Y"`

touch $indexerFile

startTime=`date +"%T on %m/%d/%Y"`
OS=`uname`

printf "Starting Time: $startTime\nHost name of run: $HOSTNAME\nOperating System of run: $OS\n\n" > $indexerFile

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

while [ $counter -le 3 ] 
do
	./indexer $DATA_PATH/lvl$counter/ $INDEX_FILE $INDEX_FILE $NEW_INDEX_FILE >> $indexerFile

	# you can use sort to order the index files to look at them else they remain unordered
	echo "Indexes have been built, read and rewritten correctly!" >> $indexerFile
	sort -o $INDEX_FILE $INDEX_FILE
	sort -o $NEW_INDEX_FILE $NEW_INDEX_FILE
	diff -q -s $INDEX_FILE $NEW_INDEX_FILE > /dev/null
	if [ $? -eq 0 ]; then # check return value of diff
		echo "Index storage passed test at lvl$counter!" >> $indexerFile
	else # files are different
		echo "Index storage didn’t pass test at lvl$counter!" >> $indexerFile
	fi

	let counter=counter+1
	#clean up any files you used
	rm -f $INDEX_FILE $NEW_INDEX_FILE

	printf "\n" >> $indexerFile
done

make clean > /dev/null

endTime=`date +"%T on %m/%d/%Y"`
printf "Ending Time: $endTime\n" >> $indexerFile
