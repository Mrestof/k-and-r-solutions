#include <stdio.h>

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
    cels = 5.0/9.0 * (fahr-32.0);
    printf("%3.0f%6.1f\n", fahr, cels);
    fahr = fahr + step;
  }

  printf("Celsius to Fahrenheit conversion table\n");
  cels = lower;
  while (cels <= upper) {
    fahr = cels * 9.0/5.0 + 32.0;
    printf("%3.0f%6.1f\n", cels, fahr);
    cels = cels + step;
  }
}
