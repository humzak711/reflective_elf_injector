#include "pkg/elf_sc.h"
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

int main() {

    // Create a file descriptor in memory
    int anon_elf_fd = memfd_create("", MFD_CLOEXEC);
    if (anon_elf_fd == -1) {
        perror("memfd_create");
        return EXIT_FAILURE;
    }

    // Write our elf into the file descriptor in memory
    write(anon_elf_fd, elf, elf_len);

    // Prepare arguments
    char *const argv[] = {NULL};
    char *const envp[] = {NULL};

    // Call fexecve to execute the elf at it's file descriptor
    if (fexecve(anon_elf_fd, argv, envp) == -1) {
        close(anon_elf_fd);
        perror("fexecve");
        return EXIT_FAILURE;
    }

    close(anon_elf_fd);
    return EXIT_SUCCESS;
}
