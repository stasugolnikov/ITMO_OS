#! /bin/bash

function check_log {
	if [[ -e /var/log/anaconda/X.log ]]
	then
		echo 0
	else
		echo -5
	fi
}

function log {
	BLUE=$(tput setaf 4)
	YELLOW=$(tput setaf 3)
	WHITE=$(tput setaf 7)

	grep "\[    [0-9]\{2\}.[0-9]\{3\}\] \((II)\|(WW)\)" /var/log/anaconda/X.log |
	sed "s/(II)/${BLUE}Information:${WHITE}/" |
	sed "s/(WW)/${YELLOW}Warning:${WHITE}/" |
	sort -r -k 3
}
