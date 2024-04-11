##
## EPITECH PROJECT, 2024
## myTeams
## File description:
## launch_client
##

COMMAND="./myteams_cli localhost"
if [ -f ./.port ]
then
    PORT=$(cat ./.port)
    echo "Trying to launch client on port $PORT"
    $COMMAND $PORT
    if [ $? -eq -1 ]
    then
        rm ./.port
    fi
else
    echo "No port file found, please launch the server first"
fi
