#include <stdio.h>
#include <math.h>

int main() {
    long double num = -123.456789;
    
    // Print the header
    printf("---------------------------------------------------------\n");
    printf("|%-15s|%-15s|%-30s|%-15s|\n", "Field 1", "Field 2", "Field 3", "Field 4");
    printf("---------------------------------------------------------\n");

    // Print the number information in a formatted table
    printf("|%15s %-30f|%-15Lf|\n", "abs", fabs(num), fabsl(num));
    printf("|%15s %-30Lf|%-15Lf|\n", "ceil", ceil(num), ceill(num));
    printf("|%15s %-30Lf|%-15Lf|\n", "floor", floor(num), floorl(num));
    printf("|%15s %-30Lf|%-15Lf|\n", "round", round(num), roundl(num));

    // Scientific notation
    printf("|%15s %-30Le|%-15Lf|\n", "scientific", num, 0.0L);

    // Decimal places rounding
    printf("|%15s %-30.1Lf|%-15Lf|\n", "to 1 dec place", num, round(num * 10) / 10);
    printf("|%15s %-30.2Lf|%-15Lf|\n", "to 2 dec place", num, round(num * 100) / 100);
    printf("|%15s %-30.3Lf|%-15Lf|\n", "to 3 dec place", num, round(num * 1000) / 1000);

    // Casting to other types
    printf("|%15s %-30d|%-15d|\n", "to int", (int)num, (int)num);
    printf("|%15s %-30ld|%-15ld|\n", "to long int", (long)num, (long)num);
    printf("|%15s %-30f|%-15f|\n", "to float", (float)num, (float)num);
    printf("|%15s %-30lf|%-15lf|\n", "to double", (double)num, (double)num);
    printf("|%15s %-30Lf|%-15Lf|\n", "to long double", num, num);

    return 0;
}


