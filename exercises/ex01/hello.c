#include <stdio.h>

int main() {
    int x = 5;
    int y = x + 1;
    printf("%i\n", y);
    return 0;
}

/*
1. Yes, the corresponding line is: movl	$5, -4(%rbp).

2. When I use the -O2 flag, there are fewer lines in
the main section and there are additional lines in the LCO
section. Specifically, these two lines are added:
.section	.text.startup,"ax",@progbits
.p2align 4,,15

3. The .sring in LCO changed to indicate that what was being
printed to the command prompt was changing. The optimization again
reduces the number of lines and adds the same lines to the LCO section.

4. In the optimized version, we no longer see x because after x is used
in the calculation for y, it is no longer needed. Instead, we see the
final value for y, which makes sense because this value is later used
in a print statement. I can conclude that optimization removes local variables
after they are no longer needed.
*/
