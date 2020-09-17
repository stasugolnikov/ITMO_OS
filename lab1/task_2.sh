#! /bin/bash

red='\033[31m'
boldface='\033[1m'
norm='\033[0m'

function check_args {
	if [[ $# < 2 ]]
	then 
		echo -en "${red}${boldface}requires 2 argumets, but $# was provided${norm}\n">&2
		exit -1
	fi
	if ! [[ -d $1 ]]
	then
		echo -en "${red}${boldface}directory does not exists ${norm}\n">&2
		exit -4
	fi
}

function search {
	check_args $1 $2
	grep -r -n $2 $1
}
