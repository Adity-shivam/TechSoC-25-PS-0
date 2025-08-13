#include <stdio.h>
#include <stdlib.h>
#define LN_2 0.69314718
#define TAYLOR_EXP_TERMS 50
#define TAYLOR_LN_TERMS 3000
#define TAYLOR_SINE_TERMS 5
#define TAYLOR_ARCSIN_TERMS 32
#define EULER 2.718281828
#define LN_10 2.302585093
#define PI 3.141592653
#define TAU 6.28318530718
#define HALF_PI 1.57079632679
#define NaN (0.0 / 0.0)
/*learned how Not a Number is implemented and checked, only floating number not
 * equal to itself to check if a var say x is NaN x!=x for x = NaN*/

/* creating basic arithmatic functions*/

double add_2(double x, double y) { return x + y; }

double subtract_2(double x, double y) { return x - y; }

double product_2(double x, double y) { return x * y; }

double divide(double x, double y) {
  if (y != 0)
    return x / y;
  else
    printf("Error Divided by zero");
  return NaN;
}

/*input real base and integral power*
 iteration for positive powers
 recursion for negative power

 and special case for 0 to handle case like 0 ^ -8 and 0^0*/

double int_power(double base, int power) {
  if (base == 0) {
    if (power <= 0) {
      printf("0^0 and 0^-ve is undefined");
      return NaN;
    } else
      return 0;
  } else if (power >= 0) {
    double result = 1;
    for (int i = 0; i < power; i++) {
      result = result * base;
    }
    return (result);

  } else
    return (1 / int_power(base, -power));
}

/*exponential using taylor series
  Factorial function can take till x <= 65
  Domain x should be non negative integer
 */

unsigned long long factorial(int x) {
  if (x >= 0) {

    if (x == 0 || x == 1)
      return 1;
    else
      return (x * factorial(x - 1));
  } else {
    printf("Error negative factorial dont exist");
    return NaN;
  }
}
/* since taylor series more accurate for terms near 0, seperate the floor and
 * fractional part*/
double exponential(double x) {
  int floor_x = (int)x;
  double frac_x = x - floor_x;
  double result = int_power(EULER, floor_x);

  double e_raised_frac_x = 1;
  for (int i = 1; i <= TAYLOR_EXP_TERMS; i++)
    e_raised_frac_x = e_raised_frac_x + int_power(frac_x, i) / factorial(i);

  result = result * e_raised_frac_x;
  return result;
}

/*natural logarithm function x = 2^p * m where m belong to [1,2)
 so ln x = p ln 2 + ln m
 since taylor series of ln only work as ln (1+x) between x belongs to (-1,1]
 Domain of ln any real belonging to (0,infinity)*/

double ln(double x) {

  if (x > 0) {
    double p = 0;
    double two_p = 1;
    while ((2 * two_p) <= x) {
      two_p = (two_p * 2);
      p = p + 1;
    }
    double m = (x / two_p);
    double result = (p * LN_2);

    double ln_m = 0;
    double y = m - 1;

    for (int i = 1; i <= TAYLOR_LN_TERMS; i++)
      ln_m = ln_m - (((int_power(-1, i)) * int_power(y, i)) / i);
    result = result + ln_m;

    return result;
  }

  else {
    printf("Out of Domain for Natural Logarithm fxn");
    return NaN;
  }
}

/*absoulute value cant use abs as it is defined in stdlib.h */
double mod(double x) {
  if (x >= 0)
    return x;
  else
    return -x;
}

/*floor fxn, cant name the fxn floor as it conflict with the floor fxn of
 * math.h*/

int flooring(double x) {
  if (x >= 0 || x == (int)x)
    return (int)x;
  else
    return (int)x - 1;
}

/* ceiling fxn, the name ceil used by math.h*/

int ceiling(double x) {
  if (x >= 0) {
    if ((int)x == x)
      return x;
    else
      return ((int)x + 1);
  } else {
    return (int)x;
  }
}
/* other logarithms like binary log , common log , log with any base */
double lb(double x) { return (ln(x) / LN_2); }
double log_10(double x) { return (ln(x) / LN_10); }

/* for log_a x x belongs to (0,infinity) and a belongs to (0,1) U (1,infinity)*/
double log_a(double x, double a) {
  if (a > 0 && a != 1)
    return (ln(x) / ln(a));
  else {
    printf("base should belong to (0,1) U (1,infinity) for real valued "
           "logarithm to be defined");
    return NaN;
  }
}
/*exponent fxn for any valid(real valued) base, exponent pair*/
double a_exp_b(double a, double b) {
  if (a > 0) {
    return (exponential(b * ln(a)));
  }

  if (a == 0) {
    if (b > 0)
      return 0;
    else if (b == 0) {
      printf("0^0 is undefined ");
      return NaN;
    } else if (b < 0) {
      printf("0 raised to negative exponent is undefined");
      return NaN;
    }
  }

  if (a < 0) {
    if (b == (int)b)
      return (int_power(a, b));

    else {
      printf("negative reals raised to non integeral powers are complex");
      return NaN;
    }
  }
}
/*sqrt fxn using a_exp_b, i know its unoptized but easy to implement and very
 * accurate*/
double sqrt(double x) { return a_exp_b(x, 0.5); }

/* TRIG TIME Taylor Series ki jai
   first i am writing a sine using 3 taylor series centered at x = pi, x= 0 and
   x = 2pi then will use sinx = sinx + 2kPi for all k belongs to Z property

   since i used 3 taylor series for different portions of principle branch i
   dont need that many terms i measure the error by graphing it on desmos
*/

double principle_branch_sine(double x) {
  if (x >= HALF_PI && x <= (3 * HALF_PI)) {
    double result = 0;
    for (int k = 0; k < TAYLOR_SINE_TERMS; k++) {
      result = result + int_power(-1, k + 1) *
                            int_power((x - PI), (2 * k) + 1) /
                            factorial((2 * k) + 1);
    }

    return (result);
  }

  else if (x >= 0 && x < HALF_PI) {
    double result = 0;
    for (int k = 1; k <= TAYLOR_SINE_TERMS; k++) {
      result = result + int_power(-1, k + 1) * int_power(x, 2 * k - 1) /
                            factorial(2 * k - 1);
    }

  } else if (x > (3 * HALF_PI) && x <= TAU) {
    double result = 0;
    for (int k = 1; k <= TAYLOR_SINE_TERMS; k++) {
      result = result + int_power(-1, k + 1) * int_power((x - TAU), 2 * k - 1) /
                            factorial(2 * k - 1);
    }
  } else {
    return NaN;
  }
}
double sin(double x) {

  if (x > TAU)
    return (sin(x - TAU));
  else if (x < 0)
    return (sin(x + TAU));
  else if (x >= 0 && x <= TAU)
    return (principle_branch_sine(x));
}

double cos(double x) { return sin(HALF_PI - x); }

double tan(double x) {
  double cosine = cos(x);
  double sine = sin(x);

  if (cosine == 0) {
    printf("Tangent is undefined for npi + pi for all n belongs to Integers");
    return NaN;
  } else
    return (sine / cosine);
}

double cot(double x) {
  double cosine = cos(x);
  double sine = sin(x);

  if (sine == 0) {
    printf("Cotangent undefined for x = npi for all n belongs to integer");
    return NaN;
  } else
    return (cosine / sine);
}

double sec(double x) {
  double cosine = cos(x);
  if (cosine == 0) {
    printf("secant undefined for npi + pi/2 for all n belong to integer");
    return NaN;
  } else
    return (1 / cosine);
}

double csc(double x) {
  double sine = sin(x);
  if (sine == 0) {
    printf("Cosecant undefined for n pi for all n belongs to integer");
    return NaN;
  } else
    return (1 / sine);
}

/* I found this series for arcsine on stackexchange
   sum_0_inf(1/2^2n)2nCn x^2n+1/2n+1
   similary using desmos i found with 100 terms i have around 3% max error at
   x = 1 with 32 terms we have around 6 % max error at x = 1 but get only
   7E-15 % error at x = 0.5

   so using the identity arcsin x = pi/2 - 2 arcsin (sqrt(1/2-x/2))
   */

unsigned long long int nCr(int n, int r) {
  int result = factorial(n);
  result = result / factorial(r);
  result = result / factorial(n - r);
  return result;
}

unsigned long long int nPr(int n, int r) {
  return (factorial(n) / factorial(n - r));
}

double arcsin(double x) {
  // TAYLOR_ARCSIN_TERMS cant be largers than 32 as my factorial only works
  // till 65 and the term need 2k factorial
  if (x >= -0.5 && x <= 0.5) {
    double result = 0;
    double term1, term2;

    for (int n = 0; n < TAYLOR_ARCSIN_TERMS; n++) {
      term1 = factorial(2 * n) / (factorial(n) * factorial(n));
      term2 = 1.0 / (int_power(4, n) * (2 * n + 1));

      result = result + term1 * term2 * (int_power(x, 2 * n + 1));
    }
    return result;
  } else if (x < -1 || x > 1) {
    printf("Domain of arcos and arcsin is [-1,1]");
    return NaN;
  } else if (x == 1) {
    return HALF_PI;
  } else if (x == -1) {
    return -HALF_PI;
  } else { // this case for (-1,-0.5)U(0.5,1)) we use arcsinx = pi/2 - 2
           // arcsin (sqrt(1/2 - x/2))
    return (HALF_PI - 2 * arcsin(sqrt((1 - x) / 2)));
  }
}
double arccos(double x) { return (HALF_PI - arcsin(x)); }

/*since Domain of arctan is (-inf , inf ) it is impossible to use a taylor
 polynomial to approximate it as arctan tends to pi/2 but any polynomial will
 tend to either +or- inf also the function is non analytic

 On stackexchange i found this series sum_0_inf((-1)^n x^2n+1 / 2n+1 ) but
 upon graphing it in desmos i found regardless of how many terms i take it
 only works between [-1,1]

 I found a trig identity that arctan x = arcsin (x/sqrt(1+x^2)) for all x
 belongs to Real*/

double arctan(double x) {
  double y = x / sqrt(1 + x * x);
  return (arcsin(y));
}

void calc(int oper) {

  switch (oper) {
  case 0: {
    exit(0);
    break;
  }

  case 1: {
    printf("enter 1st num : ");
    double x, y;
    scanf("%lf", &x);
    printf("enter 2nd num : ");
    scanf("%lf", &y);
    printf("Result = %f\n", add_2(x, y));
    break;
  }
  case 2: {
    printf("enter 1st num : ");
    double x, y;
    scanf("%lf", &x);
    printf("enter 2nd num : ");
    scanf("%lf", &y);
    printf("Result = %f\n", subtract_2(x, y));
    break;
  }

  case 3: {
    printf("enter 1st num : ");
    double x, y;
    scanf("%lf", &x);
    printf("enter 2nd num : ");
    scanf("%lf", &y);
    printf("Result = %f\n", product_2(x, y));
    break;
  }

  case 4: {
    printf("enter numerator : ");
    double x, y;
    scanf("%lf", &x);
    printf("enter denominator : ");
    scanf("%lf", &y);
    printf("Result = %f\n", divide(x, y));
    break;
  }

  case 5: {
    printf("enter argument : ");
    double x;
    scanf("%lf", &x);
    printf("Result = %f\n", sqrt(x));
    break;
  }

    /* due to floating approximations things like (-8)^(1/3) doesnt work since
    you cant use scanf to input 1/3 so the best case 0.333333333 would be
    taken as a non integeral and return NaN

    any case of (-ve)^(non integer) which should exist is not handled (yet)*/
  case 6: {
    printf("base : ");
    double x, y;
    scanf("%lf", &x);
    printf("exponent : ");
    scanf("%lf", &y);
    printf("Result = %f\n", a_exp_b(x, y));
    break;
  }

  case 7: {
    printf("enter argument : ");
    double x;
    scanf("%lf", &x);
    printf("Result = %f\n", exponential(x));
    break;
  }

  case 8: {
    printf("enter argument : ");
    double x;
    scanf("%lf", &x);
    printf("Result = %f\n", ln(x));
    break;
  }

  case 9: {
    printf("enter argument : ");
    double x;
    scanf("%lf", &x);
    printf("Result = %f\n", lb(x));
    break;
  }

  case 10: {
    printf("enter argument : ");
    double x;
    scanf("%lf", &x);
    printf("Result = %f\n", log_10(x));
    break;
  }

  case 11: {
    printf("enter argument : ");
    double x, y;
    scanf("%lf", &x);
    printf("enter base : ");
    scanf("%lf", &y);
    printf("Result = %f\n", log_a(x, y));
    break;
  }

  case 12: {
    printf("enter argument : ");
    int x;
    scanf("%d", &x); // scanf if encounter something like
    printf("Result = %llu\n", factorial(x));
    break;
  }

  case 13: {
    printf("enter n : ");
    int x, y;
    scanf("%d", &x);
    printf("enter r : ");
    scanf("%d", &y);
    printf("Result = %llu\n", nCr(x, y));
    break;
  }

  case 14: {
    printf("enter n : ");
    int x, y;
    scanf("%d", &x);
    printf("enter r : ");
    scanf("%d", &y);
    printf("Result = %llu\n", nPr(x, y));
    break;
  }

  case 15: {
    printf("enter argument : ");
    double x;
    scanf("%lf", &x);
    printf("Result = %f\n", mod(x)); // absoulte value
    break;
  }

  case 16: {
    printf("enter argument : ");
    double x;
    scanf("%lf", &x);
    printf("Result = %d\n", flooring(x));
    break;
  }

  case 17: {
    printf("enter argument : ");
    double x;
    scanf("%lf", &x);
    printf("Result = %d\n", ceiling(x));
    break;
  }

  case 18: {
    printf("enter argument : ");
    double x;
    scanf("%lf", &x);
    printf("Result = %f\n", sin(x));
    break;
  }

  case 19: {
    printf("enter argument : ");
    double x;
    scanf("%lf", &x);
    printf("Result = %f\n", cos(x));
    break;
  }

  case 20: {
    printf("enter argument : ");
    double x;
    scanf("%lf", &x);
    printf("Result = %f\n", tan(x));
    break;
  }

  case 21: {
    printf("enter argument : ");
    double x;
    scanf("%lf", &x);
    printf("Result = %f\n", cot(x));
    break;
  }

  case 22: {
    printf("enter argument : ");
    double x;
    scanf("%lf", &x);
    printf("Result = %f\n", csc(x));
    break;
  }

  case 23: {
    printf("enter argument : ");
    double x;
    scanf("%lf", &x);
    printf("Result = %f\n", sec(x));
    break;
  }

  case 24: {
    printf("enter argument : ");
    double x;
    scanf("%lf", &x);
    printf("Result = %f\n", arcsin(x));
    break;
  }

  case 25: {
    printf("enter argument : ");
    double x;
    scanf("%lf", &x);
    printf("Result = %f\n", arccos(x));
    break;
  }

  case 26: {
    printf("enter argument : ");
    double x;
    scanf("%lf", &x);
    printf("Result = %f\n", arctan(x));
    break;
  }
  default: {
    printf("Enter a valid index\n");
    break;
  }
  }
}

int main() {
  printf("Available fxns\n0  - quit\n1  - add\n2  - sub\n3  - multiply\n4  - "
         "div\n5  - "
         "sqrt\n6  - raise\n7  - exp\n8  - ln\n9  - lb\n10 - log_10\n11 - "
         "log_a\n12 - fact\n13 - nCr\n14 - nPr\n15 - mod\n16 - floor\n17 - "
         "ceil\n18 - sin\n19 - cos \n20 - tan\n21 - cot\n22 - cosec\n23 - "
         "sec\n24 - arcsin\n25 - arccos\n26 - arctan\n");

  int oper;
  /* scanf ("%d") get stuck in an infinite loop if input with non integer ,
   scanf returns 1 for successful input the second while loop "clear the bad
   input from the buffer"*/
  while (1) {
    printf("Enter operation index : ");
    int result = scanf("%d", &oper);
    if (result == 1) {
      calc(oper);
    } else {
      printf("Only Enter numbers\n");
      int ch;
      while ((ch = getchar()) != '\n' && ch != EOF)
        ;
    }
  }
}
