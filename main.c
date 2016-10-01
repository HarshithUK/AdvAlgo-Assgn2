#include <stdio.h>
#include "utils.h"

int main () {
    //find_length_of_text("hello world.text");
    int ch;
    char fname[10];
    FILE* fp;
    printf("Enter the file name: ");
    scanf("%s",fname);
    fp = fopen(fname,"r");
    do
    {
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
                     scanf("%s",pat);
                     printf("\nEnter a text range: ");
                     int tr[2];
                     scanf("%d%d",&t[0],&t[1]);
                     int c=0;
                     printf("\nWhich algorithm do you need?\n");
                     printf("\n1.Rabin-Karp");
                     printf("\n2.Knuth-Morris-Pratt");
                     printf("\n3.Suffix Trees\n");
                     do
                     {
                        printf("\nType a valid option:")
                        scanf("%d",&c);
                     }
                     while(c!=1 && c!=2 && c!=3);
                     int o[];
                     if(c==1)
                     {
                        o = find_pattern(pat,tr,&rabin_karp);
                     }
                     else if(c==2)
                     {
                        o = find_pattern(pat,tr,&knuth_morris_pratt);
                     }
                     else
                     {
                        o = find_pattern(pat,tr,&suffix_trees);
                     }
                     break;
            case 3 : build_cross_index();
                     break;
            case 4 : printf("\nEnter the size of the palindrome you want: ");
                     int s;
                     scanf("%d",&s);
                     printf("\nEnter a text range: ");
                     int tr[2];
                     scanf("%d%d",&t[0],&t[1]);
                     find_maximal_palindromes(s,t);
                     break;
            case 5 : print_stats();
                     break;
            case 6 : fclose(fp);
                     printf("\nEnter the new file name: ");
                     scanf("%s",fname);
                     fp = fopen(fname, "r");
                     break;
            default : printf("\nInvalid Option!");
        }
    }
    while(ch!=1 && ch!=2 && ch!=3 && ch!=4 && ch!=5 && ch!=6);
    print_stats();
    return 0;
}
