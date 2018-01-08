#include <stdio.h>
#include <stdlib.h>

#define MAX_N_ITEMS 2000

/*
 * Solves the below google code jam problem
 * https://code.google.com/codejam/contest/351101/dashboard#s=p0
 */

int main(int argc, char *argv[])
{
	FILE *ifp = NULL, *ofp = NULL;
	int n_testcases, credit, n_items, i, j, k, n, match_found;
	//int item_values[200]; /* Just assume that n_tems will always be <= 200 */
	int *item_values = NULL;
	
	if(argc < 3)
	{
		printf("Incorrect Use. Please provide 2 arguments: 1 input file and 1 output file\n");
		return 0;
	}
	
	ifp = fopen(argv[1], "r");
	if(ifp == NULL)
	{
		perror("Could not open Input File:\n");
		return 0;
	}
	ofp = fopen(argv[2], "w");
	if(ofp == NULL)
	{
		perror("Could not open Output File:\n");
		return 0;
	}

	item_values = malloc(sizeof(int) * MAX_N_ITEMS); /* Just assume that n_items will always be <= MAX_N_ITEMS */
	if(item_values == NULL)
	{
		printf("Could not allocate memory for %d integers\n", MAX_N_ITEMS);
		goto out;
	}
	
	fscanf(ifp, "%d", &n_testcases);
		
	for(i=0; i<n_testcases; i++)
	{
		match_found = 0;
		fscanf(ifp, "%d", &credit);
		fscanf(ifp, "%d", &n_items); 
		if(n_items > MAX_N_ITEMS)
		{
			printf("Hey! n_items is %d > %d. Your assumption is wrong\n", n_items, MAX_N_ITEMS);
			goto out;
		}
		for(j=0; j<n_items; j++)
		{
			fscanf(ifp, "%d", &item_values[j]);
		}		

		for(k = 0; k<n_items && !match_found; k++)
		{
			for(n = k+1; n<n_items && !match_found; n++)
			{
				if(item_values[k]+item_values[n] == credit)
				{
					fprintf(ofp, "Case #%d: %d %d\n", i+1, k+1, n+1); /* This test case is Done. Go to next */
					match_found = 1;
				}
			}
		}
	}

out:
	if(item_values)
		free(item_values);
	fclose(ifp);
	fclose(ofp);

	return 0;
}
