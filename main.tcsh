#!/bin/tcsh

# This tool only works on FreeBSD and linux operating systems
set operating_system = `uname -s`
if ( $operating_system != "FreeBSD" && $operating_system != "Linux" ) then
    echo "Unsupported operating system in use by the user, $operating_system"
endif

# Get the script path and directory
set script_path = `realpath $0`
set script_dir = `dirname $script_path`

# Check for the correct number of arguments
if ($#argv != 2) then
    echo "Usage: tcsh $script_path <src_ELF_path> <new_ELF_path>"
    exit 1
endif

# Set the source and new ELF paths
set src_ELF_path = "$1"
set new_ELF_path = "$2"

# Check if the source ELF file exists
if (! -e $src_ELF_path) then
    echo "$src_ELF_path could not be found"
    exit 1
endif

# Check if the file is an ELF executable
set file_type = `file -b $src_ELF_path`
if (! ( "$file_type" =~ *"ELF"* && "$file_type" =~ *"executable"* ) ) then
    echo "$src_ELF_path is not an ELF executable."
    exit 1
endif

# Set paths for the packed binary files
set bin_filepath = "$script_dir/lib/pkg/elf_sc.h"
set tmp_bin_filepath = "$script_dir/lib/pkg/elf_sc.h_tmp"
set bak_bin_filepath = "$script_dir/lib/pkg/elf_sc.h_bak"

# Create a backup of the original packed binary header file
echo "Creating backups..."
cp $bin_filepath "$bak_bin_filepath"

# Convert the ELF file to a C-style array and save it to the temporary file
xxd -i $src_ELF_path > "$tmp_bin_filepath"

# Format the variable names in the temporary file
if ( $operating_system == "FreeBSD" ) then 
    echo "Formatting variable names..."
    set formatted_varname = `echo $src_ELF_path | sed 's/\//_/g'`
    sed -i '' "s/${formatted_varname}_len/elf_len/" $tmp_bin_filepath
    sed -i '' "s/${formatted_varname}/elf/" $tmp_bin_filepath
else
    echo "Formatting variable names..."
    set formatted_varname = `echo $src_ELF_path | sed 's/\//_/g'`
    sed -i "s/${formatted_varname}_len/elf_len/" $tmp_bin_filepath
    sed -i "s/${formatted_varname}/elf/" $tmp_bin_filepath


endif

# Compile the new ELF executable
echo "Compiling new ELF..."
mv $tmp_bin_filepath $bin_filepath
gcc -o $new_ELF_path $script_dir/lib/$operating_system.c 
if ($? != 0) then
    echo "Compilation failed!"
    # Restore the backup if compilation fails
    mv $bak_bin_filepath $bin_filepath
    exit 1
endif
echo "Compiled successfully!"

# Clean up by restoring the original packed binary header file
echo "Cleaning up..."
mv $bak_bin_filepath $bin_filepath

echo "Done!"



