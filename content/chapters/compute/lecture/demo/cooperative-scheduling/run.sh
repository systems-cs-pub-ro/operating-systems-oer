#! /bin/bash

APP_NAME="app-schedule-threads"

if [[ $# > 1 ]]; then
    echo "Usage: $0 [--cooperate]"
    exit 1
fi

if [[ $# == 1 ]]; then
    COOP=$1
else 
    COOP=""
fi

cd ${APP_NAME}

kraft init -F

if [[ ${COOP} == "--cooperate" ]]; then
    echo "Running cooperative scheduling"
    kraft configure -F -y APPSCHEDULETHREADS_COOPERATE
else
    echo "Running non-cooperative scheduling"
    kraft configure -F -n APPSCHEDULETHREADS_COOPERATE
fi

kraft build

kraft run
