#!/bin/tcsh

set operating_system = `uname -s`

if ( $operating_system == "FreeBSD" ) then
    sudo pkg install xxd gcc
else
    sudo apt install xxd gcc
endif
