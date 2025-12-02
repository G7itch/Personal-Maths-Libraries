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
    char variable;
    int degree;    
    void* coeffs;
    Field coeff_field;
} Polynomial;

void* init_allocate_coeff_memory();

void input_coeffs(Polynomial *p);

Polynomial init_polynomial(char variable, int degree, Field coeff_field, void* coeffs);

void free_polynomial(Polynomial *p);

void print_polynomial(Polynomial *p);

/* TO DO */
// Polynomial add_polynomial(Polynomial *p_1, Polynomial *p_2);
// Polynomial mul_polynomial(Polynomial *p_1, Polynomial *p_2);
// Polynomial zero_polynomial();
// Polynomial scal_mul_polynomial(double lambda, Polynomial *p_1);
// etc