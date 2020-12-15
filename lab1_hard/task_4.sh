#! /bin/bash
function strlen_check_args {
	if [[ $# < 1 ]] 
	then
		echo -1
		exit
	fi
	echo 0
}

function strlen {
	echo ${#1}
}
