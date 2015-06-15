#include <assert.h>

/* Test correct synchronisation between worker+vector-partitioned loops.  */

int
main (int argc, char *argv[])
{
  int arr_a[32 * 32 * 32], arr_b[32 * 32 * 32], i;
  int num_workers, num_gangs;

  for (num_workers = 1; num_workers <= 32; num_workers <<= 1)
    for (num_gangs = 1; num_gangs <= 32; num_gangs <<= 1)
      {
	for (i = 0; i < 32 * 32 * 32; i++)
	  arr_a[i] = i;

	#pragma acc parallel copyin(arr_a) copyout(arr_b) num_gangs(num_gangs) \
		num_workers(num_workers) vector_length(32)
	{
	  int j;
	  #pragma acc loop gang
	  for (j = 0; j < 32; j++)
	    {
	      int k;

	      #pragma acc loop worker vector
	      for (k = 0; k < 32 * 32; k++)
        	arr_b[j * 32 * 32 + (1023 - k)] = arr_a[j * 32 * 32 + k] * 2;

	      #pragma acc loop worker vector
	      for (k = 0; k < 32 * 32; k++)
        	arr_a[j * 32 * 32 + (1023 - k)] = arr_b[j * 32 * 32 + k] * 2;

	      #pragma acc loop worker vector
	      for (k = 0; k < 32 * 32; k++)
        	arr_b[j * 32 * 32 + (1023 - k)] = arr_a[j * 32 * 32 + k] * 2;
	    }
	}

	for (i = 0; i < 32 * 32 * 32; i++)
	  assert (arr_b[i] == (i ^ 1023) * 8);
      }

  return 0;
}
