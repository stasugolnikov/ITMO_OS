#! /bin/bash

function search_check_args {
	if [[ $# < 2 ]]
	then 
		echo -1
		exit
	fi
	if ! [[ -d $1 ]]
	then
		echo -4
		exit
	fi
	echo 0
}

function search {
	grep -r $2 $1 2> /dev/null
}
