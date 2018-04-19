/* { dg-do compile } */
/* { dg-options "-S -O2 -fstrict-volatile-bitfields" } */
/* { dg-final { scan-assembler "st.w\t" } } */
/* { dg-final { scan-assembler "ld.w\t" } } */
/* { dg-final { scan-assembler-not "str.b" } } */



struct xxxx1 {
    unsigned int a:8;
};

struct xxxx2 {
    volatile unsigned int a:8;
};
volatile struct xxxx1 test1;
struct xxxx2 test2;

void f1()
{
    test1.a = 1;
}

void f2()
{
    test2.a = 1;
}
