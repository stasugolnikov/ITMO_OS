#! /bin/bash
. ./task_7.sh

function calc {
	if [[ $# < 3 ]] 
	then	
		echo "requires 3 arguments, but $# was provided">&2 
	       	exit -1	
	fi
	if [[ $2 =~ ^-?[[:digit:]]+$ && $3 =~ ^-?[[:digit:]]+$ ]] 
	then
		case $1 in
			'sum')
				echo $[$2 + $3]
				;;
			'sub')
				echo $[$2 - $3]
				;;
			'mul')
			       	echo $[$2 * $3]
				;;
			'div') 
				if [[ "$3" -ne "0" ]]
		       		then
	       				echo $[$2 / $3]
				else 
					echo "division by zero" >&2
					exit -1
				fi
				;;
			*)
				echo 'wrong command' >&2
				Help
		esac
	else
		echo "$2 and $3 must be integers"
	fi
}

