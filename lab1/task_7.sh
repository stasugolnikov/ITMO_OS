#! /bin/bash

RED='\033[31m'
NORMAL='\033[0m'
YELLOW='\033[33m'

function Help {
	echo -en "\t\t\t \033[44m HELP ${NORMAL}\n"
	echo -en "${YELLOW} calc: ${NORMAL}\n"
	echo -e "\t args: sum/sub/div/mul, first number, second number"
	echo -e "\t out:  result of operation on two numbers"
	echo -en "${YELLOW} search: ${NORMAL}\n"
	echo -e "\t args: directory, regular expression"
	echo -e "\t out: strings, where expression exists"
	echo -en "${YELLOW} reverse: ${NORMAL}\n"
	echo -e "\t args: file_1, file_2"
	echo -e "\t out: writes reversed file_1 in file_2"	
	echo -en "${YELLOW} strlen: ${NORMAL}\n"
	echo -e "\t args: string"
	echo -e "\t out: length of string"
	echo -en "${YELLOW} log: ${NORMAL}\n"
	echo -e "\t args: -"
	echo -e "\t out: log of warnings and information"
	echo -en "${YELLOW} exit: ${NORMAL}\n"
	echo -e "\t args: return code"
	echo -e "\t out: termination of program with entered code"
	echo -en "${YELLOW} help: ${NORMAL}\n"
	echo -e "\t args: -"
	echo -e "\t out: usage help"
	echo -en "${YELLOW} interactive: ${NORMAL}\n"
	echo -e "\t args: -"
	echo -e "\t out: interactive menu\n"
	echo -en "\033[32m Exit codes:\n"
	echo -e "\t-1 invalid number of arguments\n"
	echo -e "\t-2 invalid type of arguments\n"
	echo -e "\t-3 division by zero\n"
	echo -e "\t-4 directory does not exists\n"
	echo -e "\t-5 file does not exitst\n"
	echo -e "\t-6 non-existent command\033[0m\n"

}
