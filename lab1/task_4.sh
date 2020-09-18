#! /bin/bash
function check_args {
	if [[ $# < 1 ]] 
	then
		echo -en "\033[31m\033[1m requires 1 argument, but $# was provided\033[0m\n">&2
		exit -1
	fi
}

function strlen {
	check_args $1
	echo ${#1}
}
