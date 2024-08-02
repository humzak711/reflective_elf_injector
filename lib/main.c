#include "pkg/elf_sc.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main() {
    // Allocate memory for the ELF binary to hold our elf in memory
    void *exec_mem_elf = mmap(NULL, elf_len, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (exec_mem_elf == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Copy the ELF binary into the allocated memory so our elf is held in exec_mem_elf
    memcpy(exec_mem_elf, elf, elf_len);

    // Change the memory protection to executable
    if (mprotect(exec_mem_elf, elf_len, PROT_READ | PROT_EXEC) == -1) {
        perror("mprotect");
        munmap(exec_mem_elf, elf_len);
        exit(EXIT_FAILURE);
    }

    /* Define a function pointer holding our elf so that we can execute our elf in memory 
        by calling a function */
    typedef void (*func_elf_type)();
    func_elf_type func_elf = (func_elf_type)exec_mem_elf;

    // Execute the ELF in memory
    printf("Executing elf in memory at address: %p\n", (void *)func_elf);
    func_elf();

    // Cleanup
    munmap(exec_mem_elf, elf_len);

    return EXIT_SUCCESS;
}

