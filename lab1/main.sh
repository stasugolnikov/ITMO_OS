#! /bin/bash
. ./task_1.sh
. ./task_2.sh
. ./task_3.sh
. ./task_4.sh
. ./task_5.sh
. ./task_6.sh
. ./task_7.sh
. ./task_8.sh

case $1 in 
	'calc')
		calc $2 $3 $4
		;;
	'search')
		search $2 $3
		;;
	'reverse')
		reverse $2 $3
		;;
	'strlen')
		strlen $2
		;;
	'exit')
		([[ $# -eq 0 ]] && exit 0 || exit $1)
		;;
	'log')
		log
		;;
	'help')
		Help
		;;
	'interactive')
		interactive
		;;
		
	*) 
		echo -en "\033[31mCommand does not exists \033[m\n" >&2
		Help
		exit -6		

esac
