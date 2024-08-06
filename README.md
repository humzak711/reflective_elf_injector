*FOR EDUCATIONAL PURPOSES ONLY, WE DO NOT CONDONE ANY MISUSE OF THIS REPOSITORY, THE AUTHORS EXPECT NO LIABILITY FOR ANY MISUSE, YOU ARE RESPONSIBLE FOR YOUR OWN ACTIONS, THIS REPOSITORY WAS CREATED TO LEARN ABOUT LINUX AND FREEBSD DEVELOPMENT AND THE TCSH SCRIPTING LANGUAGE*

A tool for FreeBSD and linux which takes a given executable or .so EL file, packs it into a new executable file which will execute the given executable or .so ELF file into memory via reflective elf injection<br>
Written in tcsh (Tenex C shell) and C<br>
injected .so's must contain an `__attribute__((constructor))` to be compatible<br>

Dependencies: xxd, gcc<br>
To install dependencies: sudo tcsh setup.tcsh<br>
Usage: tcsh main.tcsh <src_ELF_path> <new_ELF_path><br>

How to install and setup:

if on arch:<br>
<code>pacman -S tcsh</code><br>
if on a debian based linux distribution:<br>
<code>sudo apt-get install tcsh</code><br>
if on FreeBSD:<br>
<code>pkg install tcsh</code><br><br>

<code>git clone https://github.com/humzak711/reflective_elf_injector.git<br>
cd reflective_elf_injector<br>
tcsh setup.tcsh</code><br>


Support for FreeBSD is currently broken, I will try to fix it soon when I have some free time
 