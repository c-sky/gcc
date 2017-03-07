
/* { dg-do compile } */

/* { dg-skip-if "Generate specific function with attribute " { csky-*-* } { "*" } { "-mistack" } }  */

void func(void) __attribute__((isr)) ;

void func(void) {;}

/* { dg-final { scan-assembler "ipop\nnir"} } */

void func1(void) __attribute__((naked)) ;

void func1(void) {;}

/* { dg-final { scan-assembler "func1:\nor\tr0, r0, r0\n\.size\t"} } */
