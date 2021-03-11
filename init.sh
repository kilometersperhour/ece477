#!/bin/bash

mkdir $1
mkdir $1/utility_programs
cp -r $2/utility_programs/ $1/
echo "$1/*.o" >> ./.gitignore
echo "$1/utility_programs" >> ./.gitignore
echo "$1/$1*" >> ./.gitignore
