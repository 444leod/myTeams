##
## EPITECH PROJECT, 2024
## myTeams
## File description:
## launch_server
##

BASE_PORT=4242
COMMAND="./myteams_server"

# //launch the command with the base port, if -1 returned, increment the port and try again
# //after, add the current port as environment variable

while [ 1 ]
do
    echo $BASE_PORT > ./.port
    echo "Trying to launch server on port $BASE_PORT"
    $COMMAND $BASE_PORT
    if [ $? -eq 84 ]
    then
        BASE_PORT=$((BASE_PORT+1))
        clear
    else
        break
    fi
done

rm ./.port
