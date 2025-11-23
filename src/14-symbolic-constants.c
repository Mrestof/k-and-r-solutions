#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

// print Fahrenheit - Celsius table for fahr = 0, 20, ..., 300 and vice versa
int main() {
  int fahr;
  printf("Fahrenheit to Celsius conversion table\n");
  for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP) {
    printf("%3d%6.1f\n", fahr, 5.0/9.0 * (fahr-32.0));
  }
}
