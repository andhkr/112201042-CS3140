// #include <stdio.h>
// #include <stdbool.h>

// // Define the types.
// typedef enum {
//     INT,
//     CHAR,
//     STRING,
//     DOUBLE,
//     FLOAT,
//     FUNCPTR,
//     VPTR,
//     BOOL,
//     // Other types like ENTRY, OP, STATEMENT can be added as needed.
// } datatype;

// // The union holding different kinds of data.
// typedef union {
//     int integer;
//     char character;
//     char* string;
//     double ldecimal;
//     float sdecimal;
//     void* (*funcptr)(void);
//     void* ptr;
//     bool boolean;
// } datavalue;

// // Accessor functions for each type.
// // They simply return a pointer to the corresponding union member.
// static inline int* get_int(datavalue *dv) {
//     return &dv->integer;
// }

// static inline char* get_char(datavalue *dv) {
//     return &dv->character;
// }

// static inline char** get_string(datavalue *dv) {
//     return &dv->string;
// }

// static inline double* get_double(datavalue *dv) {
//     return &dv->ldecimal;
// }

// static inline float* get_float(datavalue *dv) {
//     return &dv->sdecimal;
// }

// static inline bool* get_bool(datavalue *dv) {
//     return &dv->boolean;
// }

// // To avoid having to cast different function pointer types into one common type,
// // we define a union of function pointers.
// typedef union {
//     int*    (*int_func)(datavalue *);
//     char*   (*char_func)(datavalue *);
//     char**  (*string_func)(datavalue *);
//     double* (*double_func)(datavalue *);
//     float*  (*float_func)(datavalue *);
//     bool*   (*bool_func)(datavalue *);
//     // Other function pointer types can be added as needed.
// } accessor_union;

// // Build a mapping table (indexed by the enum constant) of accessor functions.
// accessor_union accessor_table[] = {
//     [INT]     = { .int_func    = get_int    },
//     [CHAR]    = { .char_func   = get_char   },
//     [STRING]  = { .string_func = get_string },
//     [DOUBLE]  = { .double_func = get_double },
//     [FLOAT]   = { .float_func  = get_float  },
//     [BOOL]    = { .bool_func   = get_bool   }
//     // You can add additional types here.
// };

// // Define separate macros for each type that directly invoke the correct accessor.
// #define FUNCTION_WHICH_I_WANT_INT(DV_PTR)    ( accessor_table[INT].int_func(DV_PTR) )
// #define FUNCTION_WHICH_I_WANT_CHAR(DV_PTR)   ( accessor_table[CHAR].char_func(DV_PTR) )
// #define FUNCTION_WHICH_I_WANT_STRING(DV_PTR) ( accessor_table[STRING].string_func(DV_PTR) )
// #define FUNCTION_WHICH_I_WANT_DOUBLE(DV_PTR) ( accessor_table[DOUBLE].double_func(DV_PTR) )
// #define FUNCTION_WHICH_I_WANT_FLOAT(DV_PTR)  ( accessor_table[FLOAT].float_func(DV_PTR) )
// #define FUNCTION_WHICH_I_WANT_BOOL(DV_PTR)   ( accessor_table[BOOL].bool_func(DV_PTR) )

// // Use token-pasting to select the right macro at compile time based on the type token.
// #define FUNCTION_WHICH_I_WANT(TYPE, DV_PTR) FUNCTION_WHICH_I_WANT_##TYPE(DV_PTR)

// int main(void) {
//     datavalue d1, d2;
    
//     // Example: d1 holds an integer, d2 holds a character.
//     d1.integer = 10;
//     d2.character = 'a';  // ASCII value 97

//     // Now, the macro call expands at compile time to the appropriate accessor:
//     // *FUNCTION_WHICH_I_WANT(INT, &d1) expands to *FUNCTION_WHICH_I_WANT_INT(&d1)
//     // and similarly for CHAR.
//     int result = *FUNCTION_WHICH_I_WANT(INT, &d1) + *FUNCTION_WHICH_I_WANT(CHAR, &d2);
//     printf("%d\n", result); // Expected output: 10 + 97 = 107

//     return 0;
// }

// #include <stdio.h>
// #include <stdbool.h>
// #include <stddef.h>

// Our enumeration of types.
// typedef enum {
//     INT=0,
//     CHAR,
//     STRING,
//     DOUBLE,
//     FLOAT,
//     FUNCPTR,
//     VPTR,
//     BOOL,
//     type_count
// } datatype;

// // The union containing various types.
// typedef union {
//     int integer;
//     char character;
//     char* string;
//     double ldecimal;
//     float sdecimal;
//     void* (*funcptr)(void);
//     void* ptr;
//     bool boolean;
// } datavalue;

// // A macro to get the pointer to the appropriate member without further casts.
// // Note: While this macro uses the conditional operator (?:) for selection,
// // it does not require you to write if-else logic at the call site.
// #define FUNCTION_WHICH_I_WANT(TYPE, DV_PTR) ( \
//     (TYPE) == INT     ? (int *)&((DV_PTR)->integer)     : \
//     (TYPE) == CHAR    ? (char *)&((DV_PTR)->character)    : \
//     (TYPE) == STRING  ? (char **)&((DV_PTR)->string)      : \
//     (TYPE) == DOUBLE  ? (double *)&((DV_PTR)->ldecimal)     : \
//     (TYPE) == FLOAT   ? (float *)&((DV_PTR)->sdecimal)      : \
//     (TYPE) == FUNCPTR ? (void*(*)(void))&((DV_PTR)->funcptr) : \
//     (TYPE) == VPTR    ? (void **)&((DV_PTR)->ptr)           : \
//     (TYPE) == BOOL    ? (bool *)&((DV_PTR)->boolean)        : \
//                        NULL \
// )
/* symbol table entry specifications and member functions*/
#include <stdio.h>
#include <float.h>
#include <assert.h>

typedef enum {
    INT,
    CHAR,
    DOUBLE,
    FLOAT,
    ENUM_COUNT  // Total number of types
} datatype;

typedef union {
    int integer;
    char character;
    double ldecimal;
    float sdecimal;
} datavalue;

typedef struct node {
    datatype type;
    datavalue exp_value;
} node;

/* Function to fetch values */
void* get_int(datavalue* d) { return &(d->integer); }
void* get_char(datavalue* d) { return &(d->character); }
void* get_double(datavalue* d) { return &(d->ldecimal); }
void* get_float(datavalue* d) { return &(d->sdecimal); }

void* (*fetch_value[ENUM_COUNT])(datavalue*) = {
    get_int,
    get_char,
    get_double,
    get_float
};

/* Function to perform addition */
datavalue add_int(void* a, void* b) { 
    datavalue res; 
    res.integer = *(int*)a + *(int*)b; 
    return res; 
}
datavalue add_char(void* a, void* b) { 
    datavalue res; 
    res.character = *(char*)a + *(char*)b; 
    return res; 
}
datavalue add_double(void* a, void* b) { 
    datavalue res; 
    res.ldecimal = *(double*)a + *(double*)b; 
    return res; 
}
datavalue add_float(void* a, void* b) { 
    datavalue res; 
    res.sdecimal = *(float*)a + *(float*)b; 
    return res; 
}

/* Function pointer array for addition */
datavalue (*add_value[ENUM_COUNT])(void*, void*) = {
    add_int,
    add_char,
    add_double,
    add_float
};

/* Function to perform addition dynamically */
datavalue perform_addition(node* n1, node* n2) {
    if (n1->type != n2->type) {
        printf("Type mismatch! Cannot add.\n");
        datavalue err = {0}; // Return default value
        return err;
    }

    void* val1 = fetch_value[n1->type](&n1->exp_value);
    void* val2 = fetch_value[n2->type](&n2->exp_value);

    return add_value[n1->type](val1, val2);
}

int main() {
    node n1, n2;

    /* Example 1: Integer Addition */
    n1.type = INT;
    n1.exp_value.integer = 10;

    n2.type = DOUBLE;
    n2.exp_value.ldecimal = DBL_MAX-15;
    n2.exp_value.integer = 0;

    assert(n2.exp_value.ldecimal != 0);
    printf("%e\n",n1.exp_value.ldecimal + n2.exp_value.ldecimal);
    // datavalue result = perform_addition(&n1, &n2);
    // printf("Result (Integer Addition): %d\n", result.integer);

    // /* Example 2: Char Addition */
    // n1.type = CHAR;
    // n1.exp_value.character = 'A';

    // n2.type = CHAR;
    // n2.exp_value.character = 2; // ASCII offset

    // result = perform_addition(&n1, &n2);
    // printf("Result (Char Addition): %c\n", result.character);

    // /* Example 3: Double Addition */
    // n1.type = DOUBLE;
    // n1.exp_value.ldecimal = 3.14;

    // n2.type = DOUBLE;
    // n2.exp_value.ldecimal = 2.71;

    // result = perform_addition(&n1, &n2);
    // printf("Result (Double Addition): %lf\n", result.ldecimal);

    return 0;
}

