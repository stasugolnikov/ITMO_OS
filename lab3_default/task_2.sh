#/bin/bash

sleep 2m &
./task_1.sh

if [[ $? -ne 0 ]]; then
    echo "Something went wrong">&2
    exit 1
fi

tail 2>/dev/null -n 0 -f ~/report &
