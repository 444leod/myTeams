##
## EPITECH PROJECT, 2024
## myTeams
## File description:
## launch_server
##

BASE_PORT=4242
COMMAND="./myteams_server"

while [ 1 ]
do
    echo $BASE_PORT > ./.port
    echo "Trying to launch server on port $BASE_PORT"
    $COMMAND $BASE_PORT
    if [ $? -eq 84 ]
    then
        BASE_PORT=$((BASE_PORT+1))
    else
        break
    fi
done

rm -f ./.port
