//all the interfaces needed
#ifndef _utils_h
#define _utils_h

/*
    *normalize multiple blank chars to single blank char
     and remove(store) website URLS that have infected text file
     using FSA based RegEx matcher
    *Accepts the file name to be pre-processed
*/
//int find_length_of_text (char* file_name);
int* rabin_karp(char* t, char* p)
{

}
int* knuth_morris_pratt(char* t, char* p)
{

}
int* suffix_trees(char* t, char* p)
{

}
int find_length_of_text(FILE* fp)
{

}
int* find_pattern(char* p, char* text, int* (*func_algo)(char*, char*))
{
}
void build_cross_index(FILE* fp, int* (*func_algo)(char*, char*))
{
}
char* find_maximal_palindromes(int s, int[] text)
{
}
void print_stats()
{
}
#endif
