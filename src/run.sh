#!/bin/bash
clear
./life $(($(tput cols )-20)) $(($(tput lines)-20))
