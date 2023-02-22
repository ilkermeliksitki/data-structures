#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PRIME 1000000007
#define MULTIPLIER 263

/* function prototypes */
int poly_hash(char *S);
char *substring(char *str, int i, int j);
void rabin_karp(char *T, char *P);

int main(void)
{
    char *pattern = malloc(sizeof(char) * 1000001);
    char *text = malloc(sizeof(char) * 1000001);
    scanf("%s %s", pattern, text);
    rabin_karp(text, pattern);
    free(pattern);
    free(text);
    return 0;
}

long long int *precomputed_hash(char *T, char *P)
{
    int T_len = strlen(T);
    int P_len = strlen(P);
    long long int *H = malloc(sizeof(long long int) * (T_len - P_len + 1));
    char *S = substring(T, T_len - P_len, T_len - 1);
    H[T_len - P_len] = poly_hash(S);
    long long int y = 1;
    for (int i = 0; i < P_len; ++i) {
        y = (y * MULTIPLIER) % PRIME;
    }
    for (int i = T_len - P_len - 1; i >= 0; i--) {
        /* recursion equation for precomputing the hash values */
        H[i] = (MULTIPLIER * H[i + 1] + T[i] - y * T[i + P_len]) % PRIME;

        /* if a value in H is negative, make it positive */
        if (H[i] <= 0) {
            H[i] += PRIME;
        }
    }
    free(S);
    return H;
}

void rabin_karp(char *T, char *P)
{
    int T_len = strlen(T);
    int P_len = strlen(P);
    int p_hash = poly_hash(P);
    long long int *H = precomputed_hash(T, P);
    for (int i = 0; i <= T_len - P_len; ++i) {
        if (p_hash != H[i]) {
            continue;
        }
        /* compare substring of T (from i to i + P_len - 1) with P */
        if (strncmp(T + i, P, P_len - 1) == 0) {
            printf("%d ", i);
        }
    }
    printf("%c", '\n');
    free(H);
    return;
}

int poly_hash(char *S)
{
    /* polynomial hash function, returns the hash value of the string */
    long long int hash = 0;
    for (int i = strlen(S) - 1; i >= 0; i--) {
        hash = (hash * MULTIPLIER + S[i]) % PRIME;
    }
    return (int)hash;
}

char *substring(char *str, int i, int j)
{
    /* return a new substring from ith index to jth index, both are inclusive */
    int len = strlen(str);
    if (i < 0 || j >= len || i > j) {
        return NULL;
    }
    char *sub = malloc(sizeof(char) * (j - i + 2));
    int k = 0;
    for (int l = i; l <= j; l++) {
        sub[k++] = str[l];
    }
    sub[k] = '\0';
    return sub;
}
