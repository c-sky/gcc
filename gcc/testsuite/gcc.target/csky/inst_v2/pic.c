
/* { dg-do compile } */
/* { dg-options "-fPIC" } */

extern int a;
extern void b(void);

void func(void)
{
    a = 1;
    b();
}

/* { dg-final { scan-assembler "grs\tgb, \.L\[0-9\]+\n\.L\[0-9\]+:\nlrw\t.+\.L\[0-9\]@GOTPC\naddu\tgb, gb,.+\nlrw\t.+@GOT"} } */
/* { dg-final { scan-assembler "lrw\t.+@PLT\naddu\t.+, gb\nld.w\t.+\njsr\t"} } */
