#include <stdio.h>
int main()
{
    FILE* myFile;
    myFile = fopen("file.txt","wt");
    fprintf(myFile,"HI");
    fclose(myFile);
    printf("Hello");
}
