A tool for FreeBSD which takes a given executable ELF file, packs it into a new executable file which will execute the given executable ELF file into memory 
Written in tcsh (Tenex C shell) and C

Dependancies: xxd, gcc
To install dependencies: tcsh setup.tcsh
Usage: tcsh main.tcsh <src_ELF_path> <new_ELF_path> 
