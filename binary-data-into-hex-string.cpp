#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 500

unsigned char buff[1024];
char curr_out[1064];

int main(void)
{
    FILE *fout = fopen("H:\\f.cpp", "w");

    if(ferror(fout))
    {
        fprintf(stderr, "Error opening output file");
        return 1;
    }
    char init_line[]  = {"unsigned char tiger_finger_vein_caffemodel[] = { "};
    const int offset_length = strlen(init_line);

    char offset_spc[offset_length];


    int count, i;
    int line_length = 0;

    memset((void*)offset_spc, (char)32, sizeof(char) * offset_length - 1);
    offset_spc[offset_length - 1] = '\0';

    fprintf(fout, "%s", init_line);

	FILE *p1 = fopen("H:\\f.caffemodel", "rb");
	//freopen("E:\\Iris\\TrainingResult\\EyeLidBottom\\sp.dat", "r", stdin);
	

	int tp = 0;
    while(!feof(p1))
    {
        count = fread(buff, sizeof(char), sizeof(buff) / sizeof(char), p1);

        for(i = 0; i < count; i++)
        {
            line_length += sprintf(curr_out, "%u,", buff[i]); //"%#x,"

            fprintf(fout, "%s", curr_out);
            if(line_length >= MAX_LENGTH - offset_length)
            {
                fprintf(fout, "\n%s", offset_spc);
                line_length = 0;
			}
			
			tp++;
        }
    }
    
    printf("%d\n",tp);
    
    fseek(fout, -2, SEEK_CUR);
    fprintf(fout, " };");

    fclose(fout);

	fclose(p1);
    return EXIT_SUCCESS;
}
