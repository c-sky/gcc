#include <iostream>
using std::cout;

#include <string.h>

class sTest {
public:
  char b[7];

  sTest(const char* str) { strcpy(b,str); }
};

int main()
{
    sTest s(". test\n");

    cout << s.b;

    return 0;

}
/* { dg-output "bounds violation.*" } */
/* { dg-do run { xfail *-*-* } } */
