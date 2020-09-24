#! /bin/bash
. ./task_1.sh
. ./task_2.sh
. ./task_3.sh
. ./task_4.sh
. ./task_5.sh
. ./task_6.sh
. ./task_7.sh
. ./task_8.sh
. ./exeption.sh
case $1 in
	'calc')
		check=$(calc_check_args $2 $3 $4)
		if [[ $check -eq 0 ]]
		then
			calc $2 $3 $4
		else
			print_error $check
			exit $check
		fi ;;
	'search')
		check=$(search_check_args $2 $3)
		if [[ $check -eq 0 ]]
		then
			search $2 $3
		else
			print_error $check
			exit $check
		fi ;;
	'reverse')
		check=$(reverse_check_args $2 $3)
		if [[ $check -eq 0 ]]
		then
			reverse $2 $3
		else
			print_error $check
			exit $check
		fi ;;
	'strlen')
		if ! [[ $# -eq 1 ]]
		then 
			strlen "$2"
		else
			print_error -1
			exit -1
		fi ;;	       
	'exit')
		check=$(exit_check_args $2)
		if [[ $check -eq 0 ]]
		then
			exit $2
		else
			print_error $check
			exit $check
		fi ;;
	'log')
		check=$(check_log)
		if [[ $check -eq 0 ]]
		then
			log
		else
			print_error $check
			exit $check
		fi ;;
	'help')
		Help ;;

	'interactive')
		interactive ;;
	*)
		print_error -6
		Help
		exit -6
esac

