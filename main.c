#include <stdio.h>
#include <stdlib.h>
#include <math.h>

bool isZero (double value);
void solveLinear(double a, double b);
void solveQuadratic(double a, double b, double c);


const double eps = 1e-7;

bool isZero ( double value){
    if ( (value <= eps) && (value >= - eps) ) return true;
    else return false;
    }

void solveLinear (double a, double b){ // ax + b = 0
    printf("Solving linear equation: %gx + (%g) = 0\n", a, b);
    if ( isZero(a) && isZero(b) ) printf ("Infinite number of roots\n");

    else if ( (isZero(a))  && ( !isZero(b) ) ) printf ("There are no roots\n");

    else if ( ( !isZero(a) ) && ( !isZero(b) ) )
        {
        double root = -b / a;
        printf ("Root of the equation is: %g\n", root);
        }
    }

void solveQuadratic (double a, double b, double c){ // ax^2 + bx + c = 0
    double root1 = 0;
    double root2 = 0;

    printf("Solving quadratic equation: %gx^2 + %gx + %g = 0\n", a, b, c);

    double dis = pow(b, 2) - 4*a*c;

    if ( dis < - eps ) printf("Discriminant below zero, no roots\n");
    else if ( isZero(dis) ) {
        root1 = -b/(2*a);
        printf("Discriminant is zero, one root: %g\n", root1);
        }
    else {
        root1 = (-b + sqrt(dis))/(2*a);
        root2 = (-b - sqrt(dis))/(2*a);
        printf("Discriminant more than zero, two roots: %g, %g\n", root1, root2);
        }
    }

int main(){
    double a = 0;// ax^2 + bx + c = 0
    double b = 0;
    double c = 0;

    printf("Equation solver 1.0 by Me: \"Solve your equation absolutely free\"\n"
           "Enter coeffs. for your equation (ax^2 + bx + c = 0)\n");
    printf("a = "); scanf("%lg", &a);
    printf("b = "); scanf("%lg", &b);
    printf("c = "); scanf("%lg", &c);
    printf("\n");

    if ( isZero(a) ) solveLinear( b, c );
    else solveQuadratic( a, b, c );

    printf("\nYour equation is solved\n");

    return 0;
    }

