#! /bin/bash

sudo apt install -y --no-install-recommends build-essential libncurses-dev \
    libyaml-dev flex git wget socat bison unzip uuid-runtime python3-pip python3

pip3 install git+https://github.com/unikraft/kraft.git@staging

kraft list update
