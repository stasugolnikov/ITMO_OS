#! /bin/bash
. ./exeption.sh
function calc_check_args {
	if [[ $# < 3 ]]
	then
		echo -1
		exit
	fi
	if ! [[ $2 =~ ^-?[[:digit:]]+$ && $3 =~ ^-?[[:digit:]]+$ ]]
	then
		echo -2
		exit
	fi
	if [[ $1 == 'div' && $3 -eq 0 ]]
	then
		echo -3
		exit
	fi
	if [[ $1 != 'sum' && $1 != 'sub' && $1 != 'mul' && $1 != 'div' ]]
	then
		echo -6
		exit
	fi
	echo 0
	exit
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
	echo $[$1 / $2]
}

function calc {
	case $1 in
		'sum') sum $2 $3 ;;
		'sub') sub $2 $3 ;;
		'mul') mul $2 $3 ;;
		'div') div $2 $3 ;;
	esac
}

