#! /bin/bash

red='\033[31m'
boldface='\033[1m'
norm='\033[0m'

function check_args {
	if [[ $# < 2 ]] 
	then
		echo -en "${red}${boldface}requires 2 arguments, but $# was provided${norm}\n">&2
		exit -1
	fi
	if ! [[ -f $1 ]]
	then 
		echo -en "${red}${boldface}file $1 does not exists${norm}\n">&2
		exit -5
	fi
}

function reverse {
	check_args $1 $2
	tac $1 | rev >$2
}
