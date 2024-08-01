A tool for FreeBSD which takes a given executable ELF file, packs it into a new executable file which will execute the given executable ELF file into memory via reflective elf injection<br>
Written in tcsh (Tenex C shell) and C<br>

Dependencies: xxd, gcc<br>
To install dependencies: tcsh setup.tcsh<br>
Usage: tcsh main.tcsh <src_ELF_path> <new_ELF_path><br>

Currently a work in progress
