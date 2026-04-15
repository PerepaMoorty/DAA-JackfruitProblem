#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ---------------- LPS ---------------- */
void compute_lps(const char *pattern, int m, int *lps)
{
    int len = 0;
    lps[0] = 0;

    int i = 1;
    while (i < m)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
                len = lps[len - 1];
            else
                lps[i++] = 0;
        }
    }
}

/* ---------------- KMP ---------------- */
void kmp_search(const char *text, const char *pattern)
{
    int n = strlen(text);
    int m = strlen(pattern);

    int *lps = (int *)malloc(m * sizeof(int));
    compute_lps(pattern, m, lps);

    int i = 0, j = 0;

    while (i < n)
    {
        if (text[i] == pattern[j])
        {
            i++;
            j++;
        }

        if (j == m)
        {
            j = lps[j - 1];
        }
        else if (i < n && text[i] != pattern[j])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    free(lps);
}

/* ---------------- BRUTE FORCE ---------------- */
void brute_force_search(const char *text, const char *pattern)
{
    int n = strlen(text);
    int m = strlen(pattern);

    for (int i = 0; i <= n - m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (text[i + j] != pattern[j])
                break;
        }
    }
}

/* ---------------- WORST CASE GENERATOR ---------------- */
void generate_worst_case(char *text, char *pattern, int n, int m)
{
    // Text: AAAAAAAA...AAB
    for (int i = 0; i < n - 1; i++)
        text[i] = 'A';
    text[n - 1] = 'B';
    text[n] = '\0';

    // Pattern: AAAAAB
    for (int i = 0; i < m - 1; i++)
        pattern[i] = 'A';
    pattern[m - 1] = 'B';
    pattern[m] = '\0';
}

/* ---------------- BENCHMARK ---------------- */
void run_benchmark()
{
    int text_sizes[] = {10000, 100000, 500000, 1000000};
    int pattern_sizes[] = {10, 50, 100, 500};

    int tests = 4;

    printf("Performance Evaluation:\n");

    for (int t = 0; t < tests; t++)
    {
        int n = text_sizes[t];
        int m = pattern_sizes[t];

        char *text = (char *)malloc(n + 1);
        char *pattern = (char *)malloc(m + 1);

        generate_worst_case(text, pattern, n, m);

        clock_t start, end;

        // KMP
        start = clock();
        kmp_search(text, pattern);
        end = clock();
        double kmp_time = (double)(end - start) / CLOCKS_PER_SEC;

        // Brute Force
        start = clock();
        brute_force_search(text, pattern);
        end = clock();
        double brute_time = (double)(end - start) / CLOCKS_PER_SEC;

        printf("\nText Size = %d | Pattern Size = %d\n", n, m);
        printf("KMP Time:         %.6f seconds\n", kmp_time);
        printf("Brute Force Time: %.6f seconds\n", brute_time);

        free(text);
        free(pattern);
    }
}

/* ---------------- MAIN ---------------- */
int main()
{
    run_benchmark();
    return 0;
}