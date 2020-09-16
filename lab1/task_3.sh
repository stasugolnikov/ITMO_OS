#! /bin/bash
function reverse {
	fin=$1
	declare -a arr
	arr=(`cat "$fin"`)
	n=${#arr[@]}
	first=0
	last=$(( ${#arr[@]} -1 ))
	while [[ first -lt last ]]
	do
		tmp="${arr[$first]}"
		arr[$first]="${arr[$last]}"
		arr[$last]="$tmp"
		(( first++, last-- ))
	done
	echo ${arr[@]} >$2
}

