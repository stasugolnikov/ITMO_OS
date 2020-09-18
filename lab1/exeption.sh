#! /bin/bash

red='\033[31m'
bold='\033[1m'
norm='\033[0m'

function print_error {
	case $1 in
		-1)
			echo -en "${red}${bold}Invalid number of arguments${norm}\n"
			;;
		-2)
			echo -en "${red}${bold}Invalid type of arguments${norm}\n"
			;;
		-3)
			echo -en "${red}${bold}Division by zero${norm}\n"
			;;
		-4)
			echo -en "${red}${bold}Directory does not exists${norm}\n"
			;;
		-5)
			echo -en "${red}${bold}File does not exists${norm}\n"
			;;
		-6)
			echo -en "${red}${bold}Non-existent command${norm}\n"
			;;
		*)
	esac
}
