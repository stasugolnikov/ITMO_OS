#/bin/bash

bash endless_loop.sh &
pid1=$!
bash endless_loop.sh &                                                          
pid2=$! 
bash endless_loop.sh &
pid3=$!

renice -n -10 -p $pid1 

kill $pid3  
