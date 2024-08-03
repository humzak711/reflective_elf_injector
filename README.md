*FOR EDUCATIONAL PURPOSES ONLY, WE DO NOT CONDONE ANY MISUSE OF THIS REPOSITORY, THE AUTHORS EXPECT NO LIABILITY FOR ANY MISUSE, YOU ARE RESPONSIBLE FOR YOUR OWN ACTIONS, THIS REPOSITORY WAS CREATED TO LEARN ABOUT LINUX AND FREEBSD DEVELOPMENT AND THE TCSH SCRIPTING LANGUAGE*

A tool for FreeBSD and linux which takes a given executable ELF file, packs it into a new executable file which will execute the given executable ELF file into memory via reflective elf injection<br>
Written in tcsh (Tenex C shell) and C<br>

Dependencies: xxd, gcc<br>
To install dependencies: sudo tcsh setup.tcsh<br>
Usage: tcsh main.tcsh <src_ELF_path> <new_ELF_path><br>

Currently a work in progress
