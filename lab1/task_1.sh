#! /bin/bash
. ./task_7.sh

boldface='\033[1m'
red='\033[31m'
norm='\033[0m'

function check_args {
	if [[ $# < 3 ]]
	then
		echo -en "${red} ${boldface}requires 3 arguments, but $# was provided${norm}\n">&2
		exit -1
	fi
	if ! [[ $2 =~ ^-?[[:digit:]]+$ && $3 =~ ^-?[[:digit:]]+$ ]]
	then
		echo -en "${boldface} ${red}arguments must be integers${norm}\n">&2
		exit -2
	fi
}

function sum {
	echo $[$1 + $2]
}
function sub {
	echo $[$1 - $2]
}
function mul {
	echo $[$1 * $2]
}
function div {
	if [[ $2 -eq 0 ]]
	then
		echo -en "${red} ${boldface}division by zero${norm}\n" >&2
		exit -3
	fi
	echo $[$1 / $2]
}

function select_case {
	case $1 in
		'sum')
			sum $2 $3
			;;
		'sub')
			sub $2 $3
			;;
		'mul')
		        mul $2 $3
			;;
		'div') 
			div $2 $3
			;;
		*)
			echo -en "${red} ${boldface}command does not exists${norm}\n">&2
			Help
	esac
}

function calc {
	check_args $1 $2 $3
	select_case $1 $2 $3
}
