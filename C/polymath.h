#pragma once
#include <stdbool.h>
#include <limits.h>

typedef enum Field {
    INTEGER,
    RATIONAL,
    REAL,
    COMPLEX,
    INT_MOD_K
} Field;

extern const char *FieldSymbols[];

typedef struct Polynomial{
    int degree;    
    void* coeffs;
    Field coeff_field;
} Polynomial;

void* allocate_coeff_memory();

void input_coeffs(Polynomial *p);

Polynomial init_polynomial(int degree, Field coeff_field);

void free_polynomial(Polynomial *p);

void print_polynomial(Polynomial *p);
