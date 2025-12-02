#pragma once

typedef enum REPRESENTATION{
    POLAR_FORM,
    CARTESIAN_FORM,
    EXPONENTIAL_FORM
} REPRESENTATION;

typedef struct Cartesian{
    double x;
    double y;
} Cartesian;

typedef struct Polar{
    double r;
    double phi;
} Polar;

typedef struct Exponential{
    double R;
    double theta;
} Exponential;

typedef struct complex{
    Cartesian cartesian;
    Polar polar;
    Exponential exponential;
} complex;

complex Complex(double x_or_r, double y_or_phi ,REPRESENTATION form);
void ComplexFormHelper(complex *c);

