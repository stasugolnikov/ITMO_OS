#/bin/bash

at -f ./task_1.sh now + 2 minutes 2>/dev/null

if [[ $? -ne 0 ]]; then
    echo "Something went wrong"
    exit 1
fi

tail 2>/dev/null -n 0 -f ~/report &
