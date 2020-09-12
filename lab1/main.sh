#! /bin/bash
. ./task_1.sh

case $1 in 
	'calc')
		calc $2 $3 $4
		;;
esac
