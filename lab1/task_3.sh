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
	text=$(tac $1 2>/dev/null)
	if [[ $? -eq 1 ]]
	then 
		echo -7
		exit
	fi

	echo 0
}

function reverse {
	text=$(tac $1 2>/dev/null)
	echo "$text" | rev>$2
}
