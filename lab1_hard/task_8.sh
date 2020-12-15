#! /bin/bash
. ./task_1.sh
. ./task_2.sh
. ./task_3.sh
. ./task_4.sh
. ./task_5.sh
. ./task_6.sh
. ./task_7.sh
. ./exeption.sh

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
			'1')
				read -p "Enter <command> <num1> <num2>: " com a b
				check=$(calc_check_args $com $a $b)
				if [[ $check -eq 0 ]]
				then 
					calc $com $a $b
				else
					print_error $check
				fi ;;
			'2')
				read -p "Enter <directory> <regular_expression>: " dir exp
				check=$(search_check_args $dir $exp)
				if [[ $check -eq 0 ]]
				then 
					search $dir $exp
				else 
					print_error $check
				fi ;;
			'3')
				read -p "Enter <file_name1> <file_name2>: " file_1 file_2
				check=$(reverse_check_args $file_1 $file_2)
				if [[ $check -eq 0 ]]
				then
					reverse $file_1 $file_2
				else
					print_error $check
				fi ;;
			'4')
				read -p "Enter <string>: " str
				check=$(strlen_check_args $str)
				if [[ $check -eq 0 ]]
				then
					strlen "$str"
				else
					print_error $check
				fi ;;
			'5')
				check=$(check_log)
				if [[ $check -eq 0 ]]
				then
					log
				else
					print_error $check
				fi ;;
			'6')
				read -p "Enter <exit_code>: " x
				check=$(exit_check_args $x)
				if [[ $check -eq 0 ]]
				then
					tput clear
					exit $x
				else	
					print_error $check
				fi ;;
			'7')
				Help ;;
			*)
				print_error -6
				Help
	
		esac
		read -s -p "Press any key to continue..." -n 1 ttt
	done
}







