#include <stdio.h>

// print Fahrenheit - Celsius table
int main() {
  int fahr;
  printf("Fahrenheit to Celsius conversion table\n");
  for (fahr = 0; fahr <= 300; fahr = fahr + 20) {
    printf("%3d%6.1f\n", fahr, 5.0/9.0 * (fahr-32.0));
  }
  printf("Fahrenheit to Celsius conversion table - reversed\n");
  for (fahr = 300; fahr >= 0; fahr = fahr - 20) {
    printf("%3d%6.1f\n", fahr, 5.0/9.0 * (fahr-32.0));
  }
}
