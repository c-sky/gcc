/* { dg-do compile } */
/* { dg-options "-S -O2 " } */

int test(int a)
{
	return (a + 0x1000);
}

/* { dg-final { scan-assembler "\[ |\t\]addi\[ |\t\]" } } */
