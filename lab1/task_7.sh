#! /bin/bash

RED='\033[31m'
NORMAL='\033[0m'
YELLOW='\033[33m'

function Help {
	echo -en "\t\t\t${RED}HELP ${NORMAL}\n"
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

	
}
