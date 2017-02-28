/* { dg-do compile } */

int func (int a, int b)
{
    return a & b;
}
/* { dg-final { scan-assembler "and" } } */

int func1 (int a)
{
    return a & (0xff);
}
/* { dg-final { scan-assembler "zextb" } } */

int func2 (int a)
{
    return a & (-0xff);
}
/* { dg-final { scan-assembler "\[ |\t\]movi\[^\n\]*\n\[ |\t\]andn" } } */

int func3 (int a)
{
    return a & (0xffffffff0);
}
/* { dg-final { scan-assembler "\[ |\t\]movi\[^\n\]*\n\[ |\t\]andn" } } */

int func4 (int a)
{
    return a & (0xff00000);
}
/* { dg-final { scan-assembler "\[ |\t\]movi\[^\n\]*\n\[ |\t\]lsli\[^\n\]*\n\[ |\t\]and" } } */

int func5 (int a)
{
    return a & (0xffff);
}
/* { dg-final { scan-assembler "zexth" } } */

int func6 (int a)
{
    return a & (0xffff0000);
}
/* { dg-final { scan-assembler "\[ |\t\]lsri\[^\n\]*\n\[ |\t\]lsli" } } */

int func7 (int a)
{
    return a & (0xffff3fff);
}
/* { dg-final { scan-assembler "\[ |\t\]movi\[^\n\]*\n\[ |\t\]lsli\[^\n\]*\n\[ |\t\]and" } } */

int func8 (int a)
{
    return a & (-0xffff);
}
/* { dg-final { scan-assembler "\[ |\t\]lrw\[^\n\]*\n\[ |\t\]andn" } } */
