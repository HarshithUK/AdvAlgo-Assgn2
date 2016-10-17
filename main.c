#include <stdio.h>
#include "utils.h"

int main()
{
    int ch;
    char fname[10];
    FILE* fp;
    printf("Enter the file name: ");
    scanf(" %[^\n]s",fname);
    fp = fopen(fname,"r");
    do
    {
        int tr[2];
        printf("\n\n---MENU---\n\n");
        printf("\n1.Find the length of the text in the file.");
        printf("\n2.Find the pattern in a given text range.");
        printf("\n3.Build a cross index from the given file.");
        printf("\n4.Find maximal palindromes in a given text range.");
        printf("\n5.Print Stats.");
        printf("\n6.Change the current working file.");
        printf("\n7.Exit\n");
        printf("\nType a valid option: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1 : printf("\nLength of the file text is : %d",find_length_of_text(fp));
                     break;
            case 2 : printf("\nEnter a pattern: ");
                     char pat[15];
                     scanf(" %[^\n]s",pat);
                     printf("\nEnter a text range: ");
                     scanf("%d%d",&tr[0],&tr[1]);
                     int c=0;
                     printf("\nWhich algorithm do you need?\n");
                     printf("\n1.Rabin-Karp");
                     printf("\n2.Knuth-Morris-Pratt");
                     printf("\n3.Suffix Trees\n");
                     do
                     {
                        printf("\nType a valid option:");
                        scanf("%d",&c);
                     }
                     while(c!=1 && c!=2 && c!=3);
                     int* o;
                     o = find_pattern(pat,tr,c);
                     int i;
                     printf("\n%d Occurrences of pattern found in indices: ",count);
                     for(i=0; i<count; ++i)
                     {
                         printf("%d ",o[i]);
                     }
                     printf("\nPreprocessing Time: %lf",preprocessing_time);
                     printf("\nSearch Time: %lf",search_time);
                     break;
            case 3 : printf("\nWhich algorithm do you need?\n");
                     printf("\n1.Rabin-Karp");
                     printf("\n2.Knuth-Morris-Pratt");
                     printf("\n3.Suffix Trees\n");
                     do
                     {
                        printf("\nType a valid option:");
                        scanf("%d",&c);
                     }
                     while(c!=1 && c!=2 && c!=3);
                     FILE* fpw = fopen("temp.txt","r");
                     build_cross_index(fpw,c);
                     break;
            case 4 : printf("\nEnter the size of the palindrome you want: ");
                     int s;
                     scanf("%d",&s);
                     printf("\nEnter a text range: ");
                     scanf("%d%d",&tr[0],&tr[1]);
                     find_maximal_palindromes(s,tr);
                     break;
            case 5 : print_stats();
                     break;
            case 6 : fclose(fp);
                     printf("\nEnter the new file name: ");
                     scanf("%s",fname);
                     fp = fopen(fname, "r");
                     break;
            case 7 : break;
            default : printf("\nInvalid Option!");
        }
    }
    while(ch!=7);
    //print_stats();
    return 0;
}
