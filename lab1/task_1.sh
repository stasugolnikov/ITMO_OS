#! /bin/bash

function calc {
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
				echo "division by 0"
				exit -1
			fi
			;;
		*)
			echo 'wrong command'
	esac
}
