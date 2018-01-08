#include <stdio.h>
#include <stdlib.h>

#define MAX_VECTOR_LEN 1000

/*
 * Solves the below google code jam problem
 * https://code.google.com/codejam/contest/32016/dashboard
 */

int compare_int_a(const void *a, const void *b)
{
        return (*(int*)a - *(int*)b);
}

int compare_int_d(const void *a, const void *b)
{
        return (*(int*)b - *(int*)a);
}

int main(int  argc, char *argv[])
{
	FILE *ifp = NULL, *ofp=NULL;
	int nr_test_cases = 0, vector_len=0, i, tc;
	int *v1=NULL, *v2=NULL;
	long long scalar_product = 0;
	
	ifp = fopen(argv[1], "r");
	if(ifp == NULL)
	{
		printf("Couldn't open input file\n");
		return 0;
	}

	ofp = fopen(argv[2], "w");
	if(ofp == NULL)
	{
		printf("Couldn't open output file\n");
		return 0;
	}

	v1 = malloc(sizeof(int) * MAX_VECTOR_LEN);
	if(v1 == NULL)
	{
		perror("malloc failed:");
		return 0;
	}

	v2 = malloc(sizeof(int) * MAX_VECTOR_LEN);
	if(v2== NULL)
	{
		perror("malloc failed:");
		return 0;
	}

	fscanf(ifp,"%d", &nr_test_cases);
	printf("test cses is %d\n", nr_test_cases);

	for(tc=0; tc<nr_test_cases; tc++)
	{
		printf("Calculating test case %d\n", tc+1);

		/* Initialize stuff */
		scalar_product = 0;
		vector_len = 0;

		fscanf(ifp, "%d", &vector_len);

		for(i=0; i<vector_len; i++)
			fscanf(ifp, "%d", v1+i);
		for(i=0; i<vector_len; i++)
			fscanf(ifp, "%d", v2+i);

		qsort(v1, vector_len, sizeof(int), compare_int_a);
		qsort(v2, vector_len, sizeof(int), compare_int_d);

		for(i=0; i<vector_len; i++)
			scalar_product += (v1[i] * v2[i]);

		fprintf(ofp, "Case #%d: %lld\n", tc+1, scalar_product);
	}

	fclose(ifp);
	fclose(ofp);
	free(v1);
	free(v2);
	return 0;
}
