#!/bin/bash

# To be run on digital ocean droplet
# opens the parameters.txt file
# for every line in parameters.txt:
	# write to an overall log file
	# train, then test (name is random string X)
	# during training -> write to X-training.txt, X-log.txt, X-maxQ.txt (make sure to write the parameters at the top of the file)
	# during testing -> write to X-performance.txt (make sure to write the parameters at the top of the file)
		# if program doesn't crash during testing, training + testing can be done in the same C++ program
		# else if it does, go in individually to read in the hashtable & run the performance tests individually
set -o noclobber
echo "set -o noclobber"
while IFS=' ' read -r line || [[ -n "$line" ]]; do
	echo $line
	unset arr
	IFS=' ' read -r -a arr <<< "$line"
	name="results/"${arr[0]}
	ep=${arr[1]}
	gamma=${arr[2]}
	n=${arr[3]}
	m=${arr[4]}
	k=${arr[5]}
	pieceset=${arr[6]}
	echo "./driver" "$ep" "$gamma" "$n" "$m" "$k" "$pieceset" "$name"-log.txt "$name"-training.txt "$name"-maxQ.txt "$name"-performance.txt
	(./driver "$ep" "$gamma" "$n" "$m" "$k" "$pieceset" "$name"-log.txt "$name"-training.txt "$name"-maxQ.txt "$name"-performance.txt & echo "$name" completed >> "$2") &
	# for word in "${arr[@]}"
	# do
	# 	echo $word
	# done
done < "$1"
