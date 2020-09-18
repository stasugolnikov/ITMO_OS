#! /bin/bash

function check_exit_code {
	if [[ $# -eq 0 ]]
	then
		echo 0
	else
		if [[ $1 =~ ^-?[[:digit:]]+$ ]]
		then
			echo $1
		else
			echo "bad"
		fi
	fi
}
