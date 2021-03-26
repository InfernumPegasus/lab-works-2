#include "textFile.h"

void reverse(char *fileName, fpos_t left, fpos_t right)
{
	FILE *file;
	char s1,s2;
	if (!(file = fopen(fileName, "r+")))
	{
		printf("File %s cannot be open\n", fileName);
		return;
	}
	
	while (left < right)
	{
		fsetpos(file, &left);
		fscanf(file,"%c",&s1);
		
		fsetpos(file, &right);
		fscanf(file,"%c",&s2);
		
		fsetpos(file, &left);
		fprintf(file,"%c",s2);
		
		fsetpos(file, &right);
		fprintf(file,"%c",s1);
		
		left++; right--;
	}
	
	fclose(file);
	return;
}