//all the interfaces needed
#ifndef _utils_h
#define _utils_h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<regex.h>
#include<time.h>

struct suff_arr {
        char* start;
        int len;
        int pos;
}*arr;

char* suff_text;
int suff_count;

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

int compar(const void *a, const void *b) {
	struct suff_arr* o1 = (struct suff_arr*) a;
	struct suff_arr* o2 = (struct suff_arr*) b;
	char* s1 = o1->start;
	char* s2 = o2->start;
	return strcmp(s1,s2);
}


int linear_search (char* str) {
	int i = 0;
    int len = strlen(str);
	for (i = 0; i < suff_count; ++i) {
		if(strncmp (arr[i].start, str, len) == 0) {
				printf("found at : %d\n", arr[i].pos);
				int j = 0;
				char* suff_text = arr[i].start;
				for (j = 0; j < len; ++j)
					printf("%c",suff_text[j]);
				printf("\n");
			}
	}
}

void create_suff_arr() {
    FILE *fp;
    char ch;
    suff_count = 0;
    fp = fopen ("test.txt", "r");
    while (1) {
        ch = fgetc (fp);
        //printf("%c", ch);
        if (ch == EOF)
            break;
        suff_count++;
    }
    fclose(fp);
	suff_count++;
    suff_text = (char*) malloc((suff_count)*(sizeof(char)));

    int i = 0;
    fp = fopen ("test.txt", "r");
    while (1) {
        ch = fgetc (fp);
        suff_text[i] = ch;
        if (ch == EOF) {
            suff_text[i] = '\0';
            break;
            }
        i++;
    }
    fclose(fp);

    arr =  (struct suff_arr*) malloc((suff_count)*(sizeof(struct suff_arr)));

    for ( i = 0; i < suff_count; i++) {
        arr[i].start = &suff_text[i];
        arr[i].len = suff_count - i;
        arr[i].pos = i;
        //printf("%c\t%d\t", *arr[i].start, arr[i].len);
    }

	qsort(arr, suff_count, sizeof(struct suff_arr), compar);

/*    for ( i = 0; i < suff_count; i++) {
        printf("%c\t%d\t", *arr[i].start, arr[i].len);
    }
*/

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

//finds all the palindromes of given length
int find_palindrome (int len) {
    int k = 0;
    int i = 0;//compares from begenning
    int j = 0;//compares form the end

    char flag = 0;

    for ( k = 0; k < count; k++) {
        i = k;
        j = k + len - 1;
        flag = 1;
        for ( ; (i-k) < (len/2); i++, j--) {
            //printf("*");
            if(suff_text[i] != suff_text[j]) {
                flag = 0;
                break;
            }
        }

        if(flag == 1) {
            printf("%d  ", k);
            for (i = k; i < (k+len); i++) {
                printf("%c", suff_text[i]);
            }
            printf("\n");
        }
    }
    return 0;
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
void build_cross_index(FILE* fp, int option)
{
    /*int ch = fgetc(fp);
    int c = 0,n = 0,st = 0;
    char **d;
    int *o;
    int index=0;
    char** story_titles;
    int nl=0,k;
    char text[100];
    int t[2] = {0,text_size};
    printf("\nCross-Index:\n");
    printf("\nWords:\n");
    while(ch!=-1)
    {
        if(ch==' ' || ch=='\n' || ch=='\t' || ch=='\r')
        {
            if(c!=0)
            {
                text[c] = 0;
                //printf("%s",text);
                int i;
                for(i=0; i<n; ++i)
                {
                    if(strcmp(text,d[i])==0)
                        break;
                }
                if(i==n)
                {
                    if(n==0)
                        d = (char**)malloc(sizeof(char*));
                    else
                        d = (char**)realloc(d,(n+1)*sizeof(char*));
                    d[n] = (char*)malloc((strlen(text))*sizeof(char));
                    strcpy(d[n],text);
                    t[0] = k;
                    //printf("%d %d %s",t[0],t[1],d[n]);
                    o = find_pattern(d[n],t,option);
                    //printf("%s",d[n]);
                    //printf("\n(%d).%s(%d):",n+1,d[n],count);
                    n++;
                    /*int j;
                    for(j=0; j<count; ++j)
                        printf(" %d",o[j]);
                }
            }
            else
            {
                if(ch=='\n')
                    nl++;
                if(nl==3)
                {
                    if(st==0)
                        story_titles = (char**)malloc(sizeof(char*));
                    else
                        story_titles = (char**)realloc(story_titles,(st+1)*sizeof(char*));
                    story_titles[st] = (char*)malloc(100*sizeof(char));
                    int j = 0;
                    ch = fgetc(fp);
                    while(ch!='\r')
                    {
                        story_titles[st][j++] = ch;
                        ch = fgetc(fp);
                    }
                    story_titles[st][j] = '\0';
                    st++;
                    nl = 0;
                }
            }
            c = 0;
        }
        else
        {
            if(c==0)
                k = index;
            text[c++] = ch;
            /*if((ch>=65 && ch<=90) || (ch>=97 && ch<=122))
            {
                if(ch>=65 && ch<=90)
                    ch += 32;
            }
            nl = 0;
        }
        ch = fgetc(fp);
        index++;
        //printf("%d %d\n",n,ch);
        if(n==10 && ch==32)
            n = 10;
    }
    printf("\n\nStory Titles:\n");
    int i;
    for(i=0; i<st; ++i)
        printf("(%d).%s\n",i+1,story_titles[i]);*/
    int n = 0,nl = 0,st = 0;
    char** d;
    char** story_titles;
    int* v;
    int ch = fgetc(fp);
    char text[100];
    int c=0, index=0, k;
    while(ch != -1)
    {
        if(ch==' ' || ch=='\n' || ch=='\t' || ch=='\r')
        {
            if(c!=0)
            {
                text[c] = 0;
                int i;
                for(i=0; i<n; ++i)
                {
                    if(strcmp(text,d[i])==0)
                        break;
                }
                if(i==n)
                {
                    if(n==0)
                    {
                        d = (char**)malloc(sizeof(char*));
                        v = (int*)malloc(sizeof(int));
                    }
                    else
                    {
                        d = (char**)realloc(d,(n+1)*sizeof(char*));
                        v = (int*)realloc(v,(n+1)*sizeof(int));
                    }
                    d[n] = (char*)malloc((strlen(text)+1)*sizeof(char));
                    v[n] = 1;
                    strcpy(d[n],text);
                    n++;
                }
                else
                    v[i]++;
                c = 0;
            }
            else
            {
                if(ch=='\n')
                    nl++;
                if(nl==3)
                {
                    if(st==0)
                        story_titles = (char**)malloc(sizeof(char*));
                    else
                        story_titles = (char**)realloc(story_titles,(st+1)*sizeof(char*));
                    story_titles[st] = (char*)malloc(100*sizeof(char));
                    int j = 0;
                    ch = fgetc(fp);
                    while(ch!='\r')
                    {
                        story_titles[st][j++] = ch;
                        ch = fgetc(fp);
                    }
                    story_titles[st][j] = '\0';
                    st++;
                    nl = 0;
                }
            }
        }
        else
        {
            if(c==0)
                k = index;
            if((ch>=65 && ch<=90) || (ch>=97 && ch<=122))
            {
                if(ch>=65 && ch<=90)
                    ch += 32;
                text[c++] = ch;
            }
            nl = 0;
        }
        ch = fgetc(fp);
        index++;
    }
    if(c>0)
    {
        text[count] = 0;
        int i;
        for(i=0; i<n; ++i)
        {
            if(strcmp(text,d[i])==0)
                break;
        }
        if(i==n)
        {
            if(n==0)
            {
                d = (char**)malloc(sizeof(char*));
                v = (int*)malloc(sizeof(int));
            }
            else
            {
                d = (char**)realloc(d,(n+1)*sizeof(char*));
                v = (int*)realloc(v,(n+1)*sizeof(int));
            }
            d[n] = (char*)malloc((strlen(text)+1)*sizeof(char));
            v[n] = 1;
            strcpy(d[n],text);
            n++;
        }
        else
            v[i]++;
        c = 0;
    }
    int i;
    for(i=0; i<n; ++i)
    {
        printf("\n%s:%d",d[i],v[i]);
    }
    printf("\n\nStory Titles:\n");
    for(i=0; i<st; ++i)
        printf("(%d).%s\n",i+1,story_titles[i]);
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
