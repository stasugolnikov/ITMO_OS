#! /bin/bash
. ./task_1.sh
. ./task_2.sh
. ./task_3.sh
. ./task_4.sh
. ./task_5.sh
. ./task_6.sh
. ./task_7.sh

function options {
	tput clear
	tput cup 1 15
	echo "Main Menu:"
	tput cup 3 12
	echo "a. calc"
	tput cup 4 12
	echo "b. search"
	tput cup 5 12
	echo "c. reverse"
	tput cup 6 12
	echo "d. strlen"
	tput cup 7 12
	echo "e. log"
	tput cup 8 12
	echo "f. exit"
	tput cup 9 12
	echo "g. help"
	tput cup 11 10
	read -p "Enter your choise [a-g]: " choise
}
function interactive {
	read -s -p "Press any key to start..." -n 1 ttt

	while :
	do
		options
		case $choise in 
			'a')
				read com a b
				calc $com $a $b
				;;
			'b')
				read dir exp
				search $dir $exp
				;;
			'c')
				read file_1 file_2
				reverse $file_1 $file_2
				;;
			'd')
				read str
				strlen $str
				;;
			'e')
				log
				;;
			'f')
				read -p "Enter the exit code: " code
				tput clear
				exit $code
				;;
			'g')
				Help
				;;
			*)
				echo -en "\033[31m\033[1mWrong command\033[0m\n">&2
				Help
				exit -6
	
		esac
		read -s -p "Press any key to continue..." -n 1 ttt
	done
}







