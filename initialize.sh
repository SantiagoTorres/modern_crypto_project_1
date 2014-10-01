#!/usr/bin/env bash

if [ ! -d "build-aux" ]
then
    mkdir build-aux
fi

aclocal --force
autoconf -f
autoheader 
automake --add-missing

if [ $? ]
then
    echo "Now you can run ./configure && make to build the project"
else
    echo "Something went really wrong...."
fi
