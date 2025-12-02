#include "polymath.h"
#include <stdio.h>
#include <stdlib.h>

const char *FieldSymbols[5] = {
    //Stores the character representations for printing
    [INTEGER] = "Z",
    [RATIONAL] = "Q",
    [REAL] = "R",
    [COMPLEX] = "C",
    [INT_MOD_K] = "Z/kZ"
};


void* allocate_coeff_memory(int degree, Field coeff_field){
    /*
    
    */
    void* ptr = NULL;
    switch (coeff_field)
    {
    case INTEGER:
    case INT_MOD_K:
        ptr = malloc(sizeof(int) * degree);
        break;
    case COMPLEX:
        // This will be filled in but requires me to write the complex library first
        break;
    default:
        // Then we either have a real or rational so same type
        ptr = malloc(sizeof(double) * degree);
    }

    return ptr;
}

void input_coeffs(Polynomial* p){
    switch(p->coeff_field)
    {
        case INTEGER:
        case INT_MOD_K:
            printf("\rEnter the integer coefficients with space delimiting: ");
            for (int i=0; i < p->degree; i++){
                scanf("%d", &((int*)p->coeffs)[i]);
            }
            break;
        case COMPLEX:
            //Coming later
            break;
        default:
            printf("\rEnter the integer coefficients with space delimiting: ");
            for (int i=0; i < p->degree; i++){
                scanf("%lf", &((double*)p->coeffs)[i]);
            }
            break;
    }
}


Polynomial init_polynomial(int degree, Field coeff_field){
    /*
    
    */
    Polynomial p;
    p.degree = degree;
    p.coeff_field = coeff_field;

    p.coeffs = allocate_coeff_memory(degree, coeff_field);
    
    if (p.coeffs == NULL){
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }

    input_coeffs(&p);

    return p;
}

void free_polynomial(Polynomial *p){
    /*
    
    */
    free(p->coeffs); //dereference then free
}

void print_polynomial(Polynomial *p){
    /*
    
    */
    printf("\n\n----------");
    printf("\nPolynomial");
    printf("\n----------");
    printf("\nDegree: %d", p->degree);
    printf("\nCoefficient field: %s\n", FieldSymbols[p->coeff_field]);
    
    switch(p->coeff_field)
    {
        case INTEGER:
        case INT_MOD_K:
            printf("\nCoefficients: ");
            for (int i=0; i < p->degree; i++){
                printf("%d ", ((int*)p->coeffs)[i]);
            }
            break;
        case COMPLEX:
            //Coming later
            break;
        default:
            printf("\nCoefficients: ");
            for (int i=0; i < p->degree; i++){
                printf("%.5f ", ((double*)p->coeffs)[i]);
            }
            break;
    }
}

int main(){
    Polynomial test = init_polynomial(2, INTEGER);
    Polynomial test2 = init_polynomial(3, REAL);
    Polynomial test3 = init_polynomial(1, INT_MOD_K);

    print_polynomial(&test);
    print_polynomial(&test2);
    print_polynomial(&test3);

    free_polynomial(&test);
    free_polynomial(&test2);
    free_polynomial(&test3);

    return 0;
}