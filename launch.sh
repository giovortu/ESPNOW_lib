#!/bin/bash

ifconfig $1 down
iwconfig $1 mode monitor
ifconfig $1 up
iwconfig $1 channel 1
bin/exec $1



