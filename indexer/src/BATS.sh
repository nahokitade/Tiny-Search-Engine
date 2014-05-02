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

while [ $counter -le 3 ] 
do
	./indexer $DATA_PATH/lvl$counter $INDEX_FILE $INDEX_FILE $NEW_INDEX_FILE

	# you can use sort to order the index files to look at them else they remain unordered
	echo "Indexes have been built, read and rewritten correctly!"
	sort -o $INDEX_FILE $INDEX_FILE
	sort -o $NEW_INDEX_FILE $NEW_INDEX_FILE
	diff -q -s $INDEX_FILE $NEW_INDEX_FILE > /dev/null
	if [ $? -eq 0 ]; then # check return value of diff
		echo "Index storage passed test at lvl$counter!"
	else
		echo "Index storage didn’t pass test at lvl$counter!" # files are different
	fi

	let counter=counter+1
	#clean up any files you used
	rm -f $INDEX_FILE $NEW_INDEX_FILE

	printf "\n"
done

make clean > /dev/null

