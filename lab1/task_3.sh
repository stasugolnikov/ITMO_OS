#! /bin/bash

function reverse_check_args {
	if [[ $# < 2 ]] 
	then
		echo -1
		exit
	fi
	if ! [[ -e $1 ]]
	then 
		echo -5
		exit
	fi
	echo 0
}

function reverse {
	tac $1 | rev >$2 2> /dev/null
}
