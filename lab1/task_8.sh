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
	echo "1. calc"
	tput cup 4 12
	echo "2. search"
	tput cup 5 12
	echo "3. reverse"
	tput cup 6 12
	echo "4. strlen"
	tput cup 7 12
	echo "5. log"
	tput cup 8 12
	echo "6. exit"
	tput cup 9 12
	echo "7. help"
	tput cup 11 10
	read -p "Enter your choise [1-7]: " choise
}
function interactive {
	read -s -p "Press any key to start..." -n 1 ttt

	while :
	do
		options
		case $choise in 
			1)
				read com a b
				calc $com $a $b
				;;
			2)
				read dir exp
				search $exp $dir
				;;
			3)
				read file_1 file_2
				reverse $file_1 $file_2
				;;
			4)
				read str
				strlen $str
				;;
			5)
				log
				;;
			6)
				read code
				exit $code
				;;
			7)
				Help
				;;
			*)
				echo "Wrong command"
	
		esac
		read -s -p "Press any key to continue..." -n 1 ttt
	done
}







