#! /bin/bash

function exit_check_args {
	if [[ $# -eq 0 || $1 =~ ^-?[[:digit:]]+$ ]]
	then
		echo 0
	else
		echo -2
	fi
}
