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
		ans=$(calc $2 $3 $4)
		#if [[ $ans =~ ^-?[[:digit:]]+$ ]]
		#then
		#	echo "$ans"
		#else
		#	echo -en "$ans\n">&2
		#fi
		echo $ans
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
		code=$(check_exit_code $2)
		if [[ $code == 'bad' ]]
		then
			echo -en "\033[31m\033[1mExit code must be integer\033[0m\n">&2
			exit -2
		else	
			exit $code
		fi
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
