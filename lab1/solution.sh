#! /bin/bash
. ./task_1.sh
. ./exeption.sh
case $1 in
	'calc')
		check=$(calc_check_args $2 $3 $4)
		if [[ $check -eq 0 ]]
		then
			calc $2 $3 $4
		else
			print_error $check
		fi ;;	
esac

