#!/bin/bash

#
# start server and stop server
#

if [ "$1" = "restart" ] || [ "$1" = "start" ]; then
	./myserver
elif [ "$1" = "stop" ]; then
	killall myserver
else 
	echo "Usage:server.sh estart[start | stop]"
fi

exit 0
