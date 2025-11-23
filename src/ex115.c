#include <stdio.h>

double fahr_to_cels(double fahr);
double cels_to_fahr(double cels);

// print Fahrenheit - Celsius table for fahr = 0, 20, ..., 300 and vice versa
int main() {
  double fahr, cels;
  int lower, upper, step;

  lower = 0;
  upper = 300;
  step = 20;

  printf("Fahrenheit to Celsius conversion table\n");
  fahr = lower;
  while (fahr <= upper) {
    printf("%3.0f%6.1f\n", fahr, fahr_to_cels(fahr));
    fahr = fahr + step;
  }

  printf("Celsius to Fahrenheit conversion table\n");
  cels = lower;
  while (cels <= upper) {
    printf("%3.0f%6.1f\n", cels, cels_to_fahr(cels));
    cels = cels + step;
  }
}

double fahr_to_cels(double fahr) {
  return 5.0/9.0 * (fahr-32.0);
}

double cels_to_fahr(double cels) {
  return cels * 9.0/5.0 + 32.0;
}
