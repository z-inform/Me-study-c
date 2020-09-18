#include <stdio.h>
#include <stdlib.h>
#include <math.h>

bool isZero (double value);
int solveLinear(double a, double b, double* root);
int solveQuadratic(double a, double b, double c, double* root1, double* root2);
int testQuad(double a, double b, double c, int num, double root1, double root2);
int testLin(double a, double b, int num, double root);
double getnum();

const double eps = 1e-7; // a < eps => a = 0
const int noRoots = -1;
const int infRoots = -2;
const double epsIgnore = 1e-4; // diifference between coeffs when a is considered 0

int main() {
    double a = 0;// ax^2 + bx + c = 0
    double b = 0;
    double c = 0;
	double root1 = 0;
	double root2 = 0;

	testQuad(3, 4, 2, noRoots, 0, 0);
	testQuad(5, 8, -9, 2, 0.762049935, -2.362049935);
	testQuad(1, 0, -4, 2, -2, 2);
	testQuad(1, 6, 9, 1, -3, 0);
	testQuad(1, 0, 0, 1, 0, 0);

	testLin(0, 0, infRoots, 0);
	testLin(0, 2, noRoots, 0);
	testLin(-3, 9, 1, 3);

    printf("Equation solver 1.0 by Me: \"Solve your equation absolutely free\"\n"
           "Enter coeffs. for your equation (ax^2 + bx + c = 0)\n");

	printf("a = ");
	a = getnum();
	
	printf("b = ");
	b = getnum();
	
	printf("c = ");
	c = getnum();

    if ( ((fabs(a / b) < epsIgnore) && (fabs(a / c) < epsIgnore)) ||
         ((fabs(a / b) < epsIgnore) && isZero(c) && !isZero(b)) ||
         ((fabs(a / c) < epsIgnore) && isZero(b) && !isZero(a)) ||
           isZero(a) )     solveLinear( b, c, &root1 );
    else solveQuadratic( a, b, c, &root1, &root2 );

    printf("\nYour equation is solved\n");

    return 0;
}

bool isZero (double value) {
	return ( fabs(value) < eps );
}

int solveLinear (double a, double b, double* root) { // ax + b = 0
    printf("Solving linear equation: %gx + (%g) = 0\n", a, b);

    if ( isZero(a) && isZero(b) ) {
		printf ("\nInfinite number of roots\n");
		return infRoots;
		}

    else if ( (isZero(a))  && ( !isZero(b) ) ) {
		printf ("\nThere are no roots\n");
		return noRoots;
		}

    else {
        *root = -b / a;
		if (isZero(*root)) *root = 0;
        printf ("\nRoot of the equation is: %g\n", *root);
		return 1;
        }
}

int solveQuadratic (double a, double b, double c, double* root1, double* root2) { // ax^2 + bx + c = 0

    printf("Solving quadratic equation: %gx^2 + %gx + %g = 0\n", a, b, c);

    double dis = pow(b, 2) - 4*a*c;

    if ( dis < - eps ){
		printf("\nDiscriminant below zero, no roots\n");
		return noRoots;
		}
    else if ( isZero(dis) ) {
        *root1 = -b/(2*a);
		if (isZero(*root1)) *root1 = 0;
        printf("\nDiscriminant is zero, one root: %g\n", *root1);
		return 1;
        }
    else {
        *root1 = (-b + sqrt(dis))/(2*a);
		if (isZero(*root1)) *root1 = 0;
        *root2 = (-b - sqrt(dis))/(2*a);
		if (isZero(*root2)) *root2 = 0;
        printf("\nDiscriminant more than zero, two roots: %g, %g\n", *root1, *root2);
		return 2;
        }
}

int testQuad (double a, double b, double c, int num, double root1, double root2) {
	double gotRoot1 = 0;
	double gotRoot2 = 0;
	int res = solveQuadratic( a, b, c, &gotRoot1, &gotRoot2 );
	if ( (res == num) && ((isZero(root1 - gotRoot1) && isZero(root2 - gotRoot2)) ||
			(isZero(root1 - gotRoot2) && isZero(root2 - gotRoot1)))) { 
		printf("Test %lg, %lg, %lg is SUCCESSFUL\n\n", a, b, c);
		return 0;
		}
		
	else {
		printf("Test %lg, %lg, %lg is FAILED. Expected num = %d, root1 = %lg, root2 = %lg. "
		 	   "Got num = %d, root1 = %lg, root2 = %lg\n\n",
			    a, b, c, num, root1, root2, res, gotRoot1, gotRoot2);	
		return 1;
		}
}

int testLin (double a, double b, int num, double root) {
	double gotRoot = 0;
	int res = solveLinear( a, b, &gotRoot);
	if ( (res == num) && (isZero(root - gotRoot)) ) {
			printf("Test %lg, %lg is SUCCESSFUL\n\n", a, b);
			return 0;
			}
	else {
		printf("Test %lg, %lg is FAILED. Expected num = %d, root = %lg. "
		 	   "Got num = %d, root = %lg\n\n",
			    a, b, num, root, res, gotRoot);
		return 1;
		}

}


double getnum(){
	double tnum = 0;
	int res = scanf("%lg", &tnum);
	while ( res == 0 ) {
		while ( getchar() != '\n' ); 
		printf("\nEnter correct number...\n");
		res = scanf("%lg", &tnum);
		}
	return tnum;
	
}












