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
                     printf("\nHow do you want to input your text range?\n");
                     printf("\n1.By two indices");
                     printf("\n2.By two distinct patterns");
                     int c=0;
                     do
                     {
                        printf("\nType a valid option:");
                        scanf("%d",&c);
                     }
                     while(c!=1 && c!=2);
                     if(c==1)
                     {
                        printf("\nEnter a text range indices: ");
                        scanf("%d%d",&tr[0],&tr[1]);
                     }
                     else
                     {
                        char p1[50];
                        char p2[50];
                        printf("\nEnter two distinct patterns: ");
                        scanf("%s%s",p1,p2);
                        int pos1 = first_occurence(p1);
                        int pos2 = first_occurence(p2);
                        if(pos2 < pos1)
                        {
                            int tempos = pos1;
                            pos1 = pos2;
                            pos2 = tempos;
                        }
                        tr[0] = pos1;
                        tr[1] = pos2;
                     }
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
                     int o;
                     o = find_pattern(pat,tr,c);
                     printf("\nOccurences : %d", o);
                     printf("\n");
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
                     build_cross_index(fp,c);
                     break;
            case 4 : printf("\nEnter the size of the palindrome you want: ");
                     int s;
                     scanf("%d",&s);
                     create_suff_arr();
                     find_palindrome(s);
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
