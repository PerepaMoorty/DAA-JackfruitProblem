#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// function to restore min-heap property
void heapify(int* h, int n, int i){
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    // "smallest" variable is changed based on which child of the current parent is smaller.

    if(left < n && h[left] < h[smallest]){
        smallest = left;
    }

    if(right < n && h[right] < h[smallest]){
        smallest = right;
    }

    if(smallest != i){
        int temp = h[i];
        h[i] = h[smallest];
        h[smallest] = temp; // parent and smaller child are swapped 
        heapify(h, n, smallest); // recursive call with new smallest element
    }
}
// function for building min-heap
void buildMinHeap(int heap[], int size){
    for(int i = (size - 1) / 2; i >= 0; i--){
        heapify(heap, size, i); // heap is reconstructed using bottom-up approach for each element.
    }
}

void kLargest(int arr[], int n, int k){
    if(k > n || k <= 0) return;

    // heap allocation
    int *heap = (int *)malloc(k * sizeof(int));
    for(int i = 0; i < k; i++){
        heap[i] = arr[i];
    }

    buildMinHeap(heap, k);

    // check remaining n-k elements
    for(int i = k; i < n; i++){
        // if current element is larger than the smallest of current top k
        if(arr[i] > heap[0]){
            heap[0] = arr[i];
            heapify(heap, k, 0);
        }
    }

    // printf("%d largest elements are: ", k);
    // for(int i = 0; i < k; i++){
    //     printf("%d ", heap[i]);
    // }
    // printf("\n");
    free(heap);
    heap=NULL;
}

// function for performance evaluation
void perf_eval(int n, int k){
    int *arr = (int *)malloc(n * sizeof(int));
    for(int i=0;i<n;i++){
        arr[i]= rand() % 100000;
    }

    clock_t start_time= clock();
    kLargest(arr, n, k);
    clock_t end_time= clock();    
    
    printf("Array Size = %10d | K = %10d | Time: %f seconds\n", n, k, (double)(end_time-start_time)/CLOCKS_PER_SEC);
    free(arr);
    arr=NULL;
}

int main(){
    printf("Performance Evaluation:\n");
    perf_eval(10, 5);
    perf_eval(1000000,500);
    perf_eval(100000000,5000);

    return 0;
}
