#! /bin/bash
. ./task_7.sh

function check_args {
	if [[ $# < 3 ]]
	then
		echo "requires 3 arguments, but $# was provided">&2
		exit -1
	fi
	if [[ $2 =~ ^-?[[:digit:]]+$ && $3 =~ ^-?[[:digit:]]+$ ]]
	then
		echo "arguments must be integers">&2
		exit -2
	fi
	if [[ $1 -eq 'div' && $3 -eq 0 ]]
	then
		echo "division by zero">&2
		exit -3
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
	echo $[$1 / $2]
}

function switch_case {
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
			echo 'command does not exists'>&2
			Help
	esac
}
