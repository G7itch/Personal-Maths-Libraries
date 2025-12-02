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


void* init_allocate_coeff_memory(int degree, Field coeff_field){
    /*
    Function to allocate the memory for the coefficients, this is variable upon their type and the amount of elements we have

    Parameters
    ----------
    degree      :   int
                    The highest natural power in the polynomial
    coeff_field :   Field
                    The field that the polynomial coefficients lie in. Taken from the enum Field, defined in polymath.h
    
    Returns
    -------
    ptr         :   void*
                    A pointer of any type to the newly allocated memory.
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
    /*
    Function for when the user wants to change the polynomial coefficients after declaring a new polynomial

    Parameters
    ----------
    p   :   Polynomial*
            A pointer to the polynomial object that you want to change the coefficients for

    Returns
    -------
    NULL
    */
    switch(p->coeff_field)
    {
        case INTEGER:
        case INT_MOD_K:
            printf("\rEnter the integer coefficients with space delimiting: ");
            for (int i=0; i < p->degree; i++){
                scanf("%d", &((int*)p->coeffs)[i]); //Type convert, then dereference, then take the address, then do pointer arithmetic.
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


Polynomial init_polynomial(char variable, int degree, Field coeff_field, void* coeffs){
    /*
    Helper function to create a polynomial object, includes basic error handling - needs to be improved

    Parameters
    ----------
    variable    :   char
                    The indeterminate to be used with the polynomial
    degree      :   degree
                    The highest natural power of the indeterminate in the polynomial
    coeff_field :   Field
                    The field of the cooefficients, taken from an enum
    coeffs      :   void*
                    A pointer of any type to a memory location containing the array of coefficients

    Returns
    -------
    p           :   Polynomial
                    The newly initialised polynomial object
    */
    Polynomial p;
    p.degree = degree;
    p.coeff_field = coeff_field;

    p.coeffs = init_allocate_coeff_memory(degree, coeff_field);
    
    if (p.coeffs == NULL){
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    
    // Error checking needs to be increased here so that we cant provide less coefficients than degree
    if (coeff_field == INTEGER || coeff_field == INT_MOD_K) {
        int* dest = (int*)p.coeffs;
        int* src  = (int*)coeffs;
        for (int i = 0; i < degree; i++)
            dest[i] = src[i];
    } else { // assume double. Here we have to change this when we add complex type
        double* dest = (double*)p.coeffs;
        double* src = (double*)coeffs;
        for (int i = 0; i < degree; i++)
            dest[i] = src[i];
    }

    return p;
}

void free_polynomial(Polynomial *p){
    /*
    Function to free up the heap allocated memory in the polynomial object. The user has to manually call this

    Parameters
    ----------
    p   :   Polynomial*
            A pointer to a polynomial object in memory. This is a memory address

    Returns
    -------
    NULL
    */
    free(p->coeffs); //dereference then free
}

void print_polynomial(Polynomial *p){
    /*
    Function to pretty print the polynomial object - needs to add symbolic representation

    Parameters
    ----------
    p   :   Polynomial*
            A pointer to a polynomial object in memory. This is a memory address

    Returns
    -------
    NULL
    */
    printf("\n\n----------");
    printf("\nPolynomial");
    printf("\n----------");
    printf("\nDegree: %d", p->degree);
    printf("\nCoefficient field: %s", FieldSymbols[p->coeff_field]);
    
    switch(p->coeff_field)
    {
        case INTEGER:
        case INT_MOD_K:
            printf("\nCoefficients: ");
            for (int i=0; i < p->degree; i++){
                printf("%d", ((int*)p->coeffs)[i]);
            }
            break;
        case COMPLEX:
            //Coming later
            break;
        default:
            printf("\nCoefficients: ");
            for (int i=0; i < p->degree; i++){
                printf("%.5f", ((double*)p->coeffs)[i]);
            }
            break;
    }
}

// Function for testing, will disappear when we make it a library
int main(){
    Polynomial test = init_polynomial('x', 2, INTEGER, (int[]){3,7});

    print_polynomial(&test);

    free_polynomial(&test);

    return 0;
}