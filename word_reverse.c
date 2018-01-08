#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1000
#define MAX_WORD_LENGTH 100

/* 
 * Solves the below google code jam problem:
 * https://code.google.com/codejam/contest/351101/dashboard#s=p1
 */

int main(int argc, char* argv[])
{
	char *line = NULL;
	char *reverse_line = NULL;
	char *word = NULL;
	FILE *ifp=NULL, *ofp=NULL;
	int s_len, i, w_len=0, k, case_nr= 0;
	int total_cases;
	int reverse_len = 0;
	int word_index = 0;

	if(argc < 3)
	{
		printf("Incorrect Usage. Supply an input and an output file\n");
		return 0;
	}

	ifp = fopen(argv[1], "r");
	if(ifp == NULL)
	{
		perror("Couldn't open input file:\n");
		return 0;	
	}

	ofp = fopen(argv[2], "w");
	if(ofp == NULL)
	{
		perror("Couldn't open output file:\n");
		return 0;	
	}

	if((line = malloc(sizeof(char) * MAX_LINE_LENGTH)) == NULL )
	{
		perror("Couldn't allocate memory\n");
		return 0;
	}	

	if ((reverse_line = malloc(sizeof(char)* MAX_LINE_LENGTH)) == NULL)
	{
		perror("Couldn't allocate memory\n");
		return 0;
	}

	word = malloc(sizeof(char) * MAX_WORD_LENGTH);
	if(word == NULL)
	{
		perror("Couldn't allocate memory\n");
		return 0;
	}
	memset(word, 0, MAX_WORD_LENGTH);

	//printf("Mmeory Allocated. Files Opened\n");
	fflush(stdout);
	fgets(line, MAX_LINE_LENGTH, ifp);

	total_cases = atoi(line);

	while(total_cases--)
	{
		fgets(line, MAX_LINE_LENGTH, ifp);
		s_len = strlen(line);
		i = s_len - 2; // remove newline and null terminating char
		k = MAX_WORD_LENGTH - 1;
		word[k--] = '\0';
		memset(reverse_line, 0, MAX_LINE_LENGTH);

		while(i >= 0)
		{
			if(line[i] != ' ' && i != 0)
			{
				word[k--] = line[i];
				++w_len;
			}
			else
			{
				if(i == 0)
				{
					word[k--] = line[i];
					++w_len;
				}

				/* At this point we encountered a word. So write it to reverse string */

				word_index = MAX_WORD_LENGTH - w_len - 1;

				while(w_len--)
				{
					reverse_line[reverse_len++] = word[word_index++];
				}

				/* Add a space */
				reverse_line[reverse_len++] = ' ';

				memset(word, 0, MAX_WORD_LENGTH);
				w_len = 0;
				k = MAX_WORD_LENGTH - 1;
				word[k--] = '\0';
			}
			--i;
		}
		
		fprintf(ofp, "Case #%d: %s\n", ++case_nr, reverse_line);
		reverse_len = 0;
		memset(line, 0, MAX_LINE_LENGTH);
	}

	fclose(ifp);
	fclose(ofp);
	return 0;
}
