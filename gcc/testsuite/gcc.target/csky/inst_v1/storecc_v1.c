/* { dg-do compile } */
/* { dg-final { scan-assembler "\tcmpne\t\.*\tmvc\t" } } */

int storecc(int a,int b)
{
	return (a != b);
}
