//all the interfaces needed
#ifndef _utils_h
#define _utils_h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<regex.h>
#include<time.h>
typedef int* (*func_algo)(char*, char*);
char url[20][100];
double preprocessing_time;
double search_time;
int count=0,count_url=0;
int algo;
int text_size;
double time_elapsed(struct timespec start, struct timespec end)
{
	double t;
	t = (end.tv_sec - start.tv_sec) * 1000;
	t += (end.tv_nsec - start.tv_nsec) * 0.000001;
	return t;
}
int* rabin_karp(char* text, char* pat)
{
    struct timespec start, end;
    algo = 1;
    static int occur[1000];
    int q = 997,d = 128;
    int n = strlen(text);
    int m = strlen(pat);
    int h = 1,i;
    for(i=1; i<m; ++i)
        h *= d;
    h = h%q;
    int p=0;
    int t[n-m+1];
    t[0] = 0;
    clock_gettime(CLOCK_REALTIME, &start);
    for(i=0; i<m; ++i)
    {
        p = ((d*p)+pat[i])%q;
        t[0] = ((d*t[0])+text[i])%q;
    }
    clock_gettime(CLOCK_REALTIME, &end);
    preprocessing_time = time_elapsed(start, end);
    clock_gettime(CLOCK_REALTIME, &start);
    int s;
    for(s=0; s<=n-m; ++s)
    {
        if(p==t[s])
        {
            int i;
            for(i=0; i<m; ++i)
            {
                if(pat[i]!=text[s+i])
                    break;
            }
            if(i==m)
            {
                occur[count++] = s;
            }
        }
        if(s<n-m)
        {
            t[s+1] = (d*(t[s]-(text[s]*h)))+text[s+m];
            t[s+1] = t[s+1]%q;
            if(t[s+1]<0)
            {
                t[s+1] += q;
            }
        }
    }
    clock_gettime(CLOCK_REALTIME, &end);
    search_time = time_elapsed(start, end);
    return occur;
}
int* com_pre_fun (char* p) {
    //printf("%s\n", p);
    int m = strlen(p);
    int i = 0;
    int *pi = malloc((sizeof(int)*m));
    for ( i = 0; i < m; i++) {
        pi[i] = 0;
    }
    pi[0] = 0;
    int k = 0;
    int q = 0;

    for (q = 1; q < m; q++) {
        while (k > 0 && p[k] != p[q]){
            k = pi[k-1];
        }
        if (p[k] == p[q])
        k += 1;
        pi[q] = k;
    }
    return pi;
}

int kmp_matcher(char* t, char* p) {
        int n = strlen(t);
        int m = strlen(p);
        int* pi = com_pre_fun(p);
        int q = 0;
        int i = 0;
        for ( i = 0; i < n; i++) {
            while (q > 0 && p[q] != t[i]) {
                q = pi[q-1];
            }
            if (p[q] == t[i])
            q += 1;
            if(q == m) {
                printf("match found at %d\n",(i-m+1));
                q = pi[q-1];
            }
        }
}

int* suffix_trees(char* t, char* p)
{
    algo = 3;
}
int find_length_of_text(FILE* fp)
{
    char text[100];
    char* regexString = "(http|https|ftp):\/\/[^ \n\t\r\v]+";
    FILE* fpw = fopen("temp.txt","w");
    regex_t regexCompiled;
    int c = fgetc(fp);
    int s;
    int cnt=0,len=0;
    if(regcomp(&regexCompiled, regexString, REG_EXTENDED))
    {
        printf("Could not compile regular expression.\n");
        return -1;
    }
    while(c!=-1)
    {
        if(c==32 && s!=1)
        {
            s = 1;
            regmatch_t g[1];
            int m;
            while(regexec(&regexCompiled, text, 1, g, 0) == 0)
            {
                int i;
                char temp[100];
                char strcopy[100];
                strcpy(strcopy,text);
                strcopy[g[0].rm_eo] = 0;
                printf("%u-%u:%s\n",g[0].rm_so,g[0].rm_eo,strcopy);
                strcpy(temp,text);
                for(i=g[0].rm_eo; i<strlen(temp); ++i)
                    text[i-g[0].rm_eo] = temp[i];
                text[strlen(temp)-g[0].rm_eo] = '\0';
            }
            fputs(text,fpw);
            fputc(c,fpw);
            len++;
            cnt = 0;
        }
        else if(c!=32)
        {
            s = 0;
            len++;
            text[cnt++] = c;
        }
        c = fgetc(fp);
    }
    fclose(fpw);
    text_size = len;
    return len;
}
int* find_pattern(char* p, int t[], int option)
{
    FILE* fpw = fopen("temp.txt","r");
    char text[t[1]-t[0]+1];
    int i,c = 0,a = 0;
    int ch = fgetc(fpw);
    while(ch!=-1)
    {
        if(c>=t[0] && c<t[1])
            text[a++] = (char)ch;
        c++;
        ch = fgetc(fpw);
    }
    int *o;
    if(option==1)
        o = rabin_karp(p,text);
    else if(option==2)
        o = knuth_morris_pratt(p,text);
    else
        o = suffix_trees(p,text);
    return o;
}
void build_cross_index(FILE* fp, func_algo f)
{
}
char* find_maximal_palindromes(int s, int text[])
{
}
void print_stats()
{
    printf("\nSTATISTICS:\n\n");
    printf("Text Size Used : %d\n",text_size);
    printf("URL Infection List :\n");
    int i;
    for(i=0; i<count_url; ++i)
    {
        printf("(%d). %s\n",i+1,url[i]);
    }
    printf("Algorithm Used : ");
    if(algo==1)
        printf("Rabin-Karp\n");
    else if(algo==2)
        printf("Knuth-Morris-Pratt\n");
    else
        printf("Suffix trees\n");
    printf("Preprocessing Time : %lf\n",preprocessing_time);
    printf("Search Time : %lf\n",search_time);
}
#endif
