#include "compmath.h"
#include <stdio.h>

complex Complex(double x_or_mod, double y_or_arg ,REPRESENTATION form){
    complex c = {0};
    switch (form)
    {
    case CARTESIAN_FORM:
        c.cartesian.x = x_or_mod;
        c.cartesian.y = y_or_arg;
        break;
    case EXPONENTIAL_FORM:
    case POLAR_FORM:
        c.polar.r = x_or_mod;
        c.polar.phi = y_or_arg;
        c.exponential.R = x_or_mod;
        c.exponential.theta = y_or_arg;
        break;
    default:
        break;
    }
    return c;
}

void ComplexFormHelper(complex *c){
    printf("\n\n\n");
    printf("\rComplex form helper");
    printf("---------------------\n");
    printf("Exponential form looks like: R*e^{theta*i}\n");
    printf("Polar form looks like: R(cos(theta)+i*sin(theta))\n");
    printf("Cartesian form looks like: x+y*i\n");
    printf("----------------------------------------------------\n");
    printf("For the provided complex number:\n");
    printf("Exponential: %.3lf*e^{%.5lf * i}\n",c->exponential.R,c->exponential.theta);
    printf("Polar: %.3lf(cos(%.5lf)+i*sin(%.5lf))",c->polar.r,c->polar.phi);
    printf("\n\n\n");
}

int main(){
    complex test = Complex(1,2,EXPONENTIAL_FORM);
    printf("%lf",test.polar.r);
    return 0;
}