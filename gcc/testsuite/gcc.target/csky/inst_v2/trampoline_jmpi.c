/* { dg-do compile } */
/* { dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=ck801" "-march=ck802" }  { ""  }  }  */

void func(int (*param)(int));

void outer(int x, int z)
{
  int nested(int y)
    {
      return x + y + z;
    }
  func(nested);
}

/* { dg-final { scan-assembler "lrw\tt0, \\\[\.Lstatic_chain\\\]\n\tjmpi\t\\\[.Lfunc_address\\\]" } } */
