#!/bin/bash

cat <<EOF >/dev/null
192. Word Frequency
Medium

Write a bash script to calculate the frequency of each word in a text file words.txt.

For simplicity sake, you may assume:

    words.txt contains only lowercase characters and space ' ' characters.
    Each word must consist of lowercase characters only.
    Words are separated by one or more whitespace characters.

Example:

Assume that words.txt has the following content:

the day is sunny the the
the sunny is is

Your script should output the following, sorted by descending frequency:

the 4
is 3
sunny 2
day 1

Note:

    Don't worry about handling ties, it is guaranteed that each word's frequency count is unique.
    Could you write it in one-line using Unix pipes?

Accepted
20,285
Submissions
75,628
EOF

words=$(cat words.txt)
#[ -z "$words" ] && words=$(echo 'the day is sunny the the the sunny is is')
#[ -z "$words" ] && words=$(echo 'a a aa')
[ -z "$words" ] && words=$(echo 'how many cans can a canner can if a canner can can cans\na canner can can as many cans as a canner can if a canner can can a can\na canner can can as many cans as a canner can cans')

words_sorted=$(echo -e "$words" | sed -r -e 's/\s+/\n/g' | sort)
words_uniq=$(echo -e "$words_sorted" | uniq)
#echo -e "$words_uniq"
output=
for w in $words_uniq; do
	#echo cnt $w
	cnt=$(echo -e "$words_sorted" | grep -c -- "\b$w\b")
	#echo $w $cnt
	[ -n "$output" ] && output="$output\n$w $cnt" || output="$w $cnt"
done
echo -e "$output" | sort -k 2 -r -h

### leetcode sample solution
# cat words.txt | tr -s " " "\n" | sort | uniq -c | sort -r | awk '{print $2, $1}'