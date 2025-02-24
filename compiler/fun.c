#include <stdio.h>
#include <setjmp.h>

extern jmp_buf buf;  // Use the global jump buffer

void recursive_function(int depth) {
    printf("Recursion depth: %d\n", depth);
    
    if (depth == 5) {  // Condition met: jump to break_loop
        printf("Condition met, jumping to break_loop!\n");
        longjmp(buf, 1);  // Jump back to setjmp() in `main.c`
    }

    recursive_function(depth + 1);
}
