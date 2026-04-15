#include <stdio.h>
#include <stdlib.h>

int merge_and_count(int A[], int temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;
    int inv_count = 0;

    while (i <= mid && j <= right) {
        if (A[i] <= A[j]) {
            temp[k++] = A[i++];
        } else {
            temp[k++] = A[j++];
            inv_count += (mid - i + 1);
        }
    }

    while (i <= mid) {
        temp[k++] = A[i++];
    }

    while (j <= right) {
        temp[k++] = A[j++];
    }

    for (int x = left; x <= right; x++) {
        A[x] = temp[x];
    }

    return inv_count;
}

int count_inversions(int A[], int temp[], int left, int right) {
    int inv_count = 0;

    if (left < right) {
        int mid = (left + right) / 2;

        inv_count += count_inversions(A, temp, left, mid);
        inv_count += count_inversions(A, temp, mid + 1, right);
        inv_count += merge_and_count(A, temp, left, mid, right);
    }

    return inv_count;
}

int main() {
    int A[] = {2, 4, 1, 3, 5};
    int n = sizeof(A) / sizeof(A[0]);

    int *temp = (int *)malloc(n * sizeof(int));

    int result = count_inversions(A, temp, 0, n - 1);

    printf("Number of inversions: %d\n", result);

    free(temp);
    return 0;
}

