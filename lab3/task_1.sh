#!/bin/bash

date=$(date +"%F_%T")

mkdir ~/test 2>/dev/null && {
    echo "catalog test was created successfully" > ~/report 2>/dev/null;
    touch ~/report/$date 2>/dev/null;
} 
ping net_nikogo.ru 2>/dev/null ||
echo "${date} host is unavaliable" >> ~/report
