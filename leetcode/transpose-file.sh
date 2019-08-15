#!/bin/bash

cat <<EOF >/dev/null
194. Transpose File
Medium

Given a text file file.txt, transpose its content.

You may assume that each row has the same number of columns and each field is separated by the ' ' character.

Example:

If file.txt has the following content:

name age
alice 21
ryan 30

Output the following:

name alice ryan
age 21 30

 
Accepted
10,600
Submissions
45,373
EOF

file_txt="name age
alice 21
ryan 30"
echo -e "$file_txt" > file.txt
file=($(cat file.txt))

#echo ${file[0]}

cols=$(head -n 1 file.txt | wc -w)
rows=$((${#file[*]}/cols))

for ((i=0;i<cols;i++)); do
	for ((j=0;j<rows;j++)); do
		# file[j][i]
		echo -n "${file[((j*cols+i))]}"
		if ((j!=rows-1)); then
			echo -n " "
		fi
	done
	echo
done

### or use cut ### clue from 0ms sample solution from leetcode
for ((i=1;i<=cols;i++)); do
	cut -d' ' -f $i file.txt | xargs
done