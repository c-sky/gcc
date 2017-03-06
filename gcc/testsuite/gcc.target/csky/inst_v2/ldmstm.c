
/* { dg-do compile } */

/* { dg-skip-if "Generate code with stm instruction" { csky-*-* } { "*" } { "-O2 -mmultiple-stld -mno-pushpop" } }  */

int func(int a1,  int a2,  int a3,  int a4,
         int a5,  int a6,  int a7,  int a8,
         int a9,  int a10, int a11, int a12,
         int a13, int a14, int a15, int a16)
{
    int b1 = a1;
    int b2 = a2 + a1;
    int b3 = a3 + a2;
    int b4 = a4 + a3;
    int b5 = a5 + a4;
    int b6 = a6 + a5;
    int b7 = a7 + a6;
    int b8 = a8 + a7;
    int b9 = a9 + a8;
    int b10 = a10 + a9;
    int b11 = a11 + a10;
    int b12 = a12 + a11;
    int b13 = a13 + a12;
    int b14 = a14 + a15;

    return b1 + b2 + b3 + b4 + b5 + b6 + b7 + b8
           + b9 + b10 + b11 + b12 + b13 + b14;
}

/* { dg-final { scan-assembler "ldm\t"} } */
