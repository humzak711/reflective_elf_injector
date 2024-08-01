#include "pkg/elf_sc.h"
#include <elf.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main() {
    
   // Call the memfd_create subroutine to create an anonymous file descriptor
    int anon_fd = memfd_create("", MFD_CLOEXEC);
    if (anon_fd == -1) {
        perror("memfd_create");
        exit(EXIT_FAILURE);
    }

    // Write the elf to the anonymous file descriptor
    write(anon_fd, elf, elf_len);

    // Construct a string variable to hold the anonymous file descriptor's path
    char *anon_fd_path;
    /* To do: construct the filepath to the path of the file descriptor for FreeBSD 
       as currently it constructs the filepath to paths of file descriptor's for linux,
       replace /proc/self/fd/%i with what the file path for the file descriptor would 
       be in FreeBSD */
    asprintf(&anon_fd_path, "/proc/self/fd/%i", anon_fd);

    // Call execl on the anonymous file descriptor's path to execute the elf
    if (execl(anon_fd_path, NULL) == -1) {
        perror("execl");
        exit(EXIT_FAILURE);
    }

    /* The code here will not be executed if successful since the process will now 
       hold the elf that has been executed in memory */
    return EXIT_SUCCESS;
}
