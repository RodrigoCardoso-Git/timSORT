#include <stdio.h>
#include <stdlib.h>

// Tamanho mínimo de uma "run" (subsequência ordenada)
#define MIN_MERGE 32

// Função para ordenar uma subsequência usando Insertion Sort
void insertion_sort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Função para mesclar duas runs ordenadas
void merge(int arr[], int l, int m, int r) {
    int len1 = m - l + 1, len2 = r - m;
    int *left = (int *)malloc(len1 * sizeof(int));
    int *right = (int *)malloc(len2 * sizeof(int));

    // Copia os elementos para os arrays temporários
    for (int i = 0; i < len1; i++) {
        left[i] = arr[l + i];
    }
    for (int i = 0; i < len2; i++) {
        right[i] = arr[m + 1 + i];
    }

    // Mescla os arrays temporários de volta ao array original
    int i = 0, j = 0, k = l;
    while (i < len1 && j < len2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de left[], se houver
    while (i < len1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de right[], se houver
    while (j < len2) {
        arr[k] = right[j];
        j++;
        k++;
    }

    // Libera a memória alocada
    free(left);
    free(right);
}

// Função principal do TimSort
void timsort(int arr[], int n) {
    // Ordena pequenas runs com Insertion Sort
    for (int i = 0; i < n; i += MIN_MERGE) {
        int end = (i + MIN_MERGE - 1 < n - 1) ? i + MIN_MERGE - 1 : n - 1;
        insertion_sort(arr, i, end);
    }

    // Mescla as runs
    for (int size = MIN_MERGE; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = (left + 2 * size - 1 < n - 1) ? left + 2 * size - 1 : n - 1;
            if (mid < right) {
                merge(arr, left, mid, right);
            }
        }
    }
}

// Função para imprimir o array
void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Exemplo de uso
int main() {
    int arr[] = {5, 21, 7, 23, 19, 3, 1, 9, 8, 2, 4, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array original: ");
    print_array(arr, n);

    timsort(arr, n);

    printf("Array ordenado: ");
    print_array(arr, n);

    return 0;
}
