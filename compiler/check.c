#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;  // Declare globally accessible jump buffer

void recursive_function(int);  // Function prototype

int main() {
    if (setjmp(buf) == 0) {
        // First time execution: call recursive function
        printf("Starting recursion...\n");
        recursive_function(0);
    } else {
        // Execution resumes here when longjmp is called
        printf("Jumped to break_loop label!\n");
    }

    printf("Program exited safely.\n");
    return 0;
}
