#include <stdio.h>
#include <stdlib.h>

// Função para ajustar o heap para cima (heapify up)
void heapify_up(float *arr, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2; // Calcula o índice do pai
        if (arr[index] > arr[parent]) {
            // Troca o valor com o pai se for maior
            float temp = arr[index];
            arr[index] = arr[parent];
            arr[parent] = temp;
        } else {
            break; // Se a propriedade do heap estiver mantida, pare
        }
        index = parent; // Continue verificando o próximo ancestral
    }
}

// Função para ajustar o heap para baixo (heapify down)
void heapify_down(float *arr, int n, int index) {
    int largest = index; // Assume que o maior está na raiz
    int left = 2 * index + 1; // Índice do filho esquerdo
    int right = 2 * index + 2; // Índice do filho direito

    // Verifica se o filho esquerdo é maior que a raiz
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // Verifica se o filho direito é maior que o maior até agora
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // Se o maior não for a raiz, troca e continua ajustando
    if (largest != index) {
        float temp = arr[index];
        arr[index] = arr[largest];
        arr[largest] = temp;

        // Recursivamente ajusta o subheap afetado
        heapify_down(arr, n, largest);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    float *arr = (float *)malloc(n * sizeof(float));
    if (arr == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        return 1;
    }

    // Lê o array
    for (int i = 0; i < n; i++) {
        scanf("%f", &arr[i]);
    }

    // Organiza o array como um heap
    for (int i = 0; i < n; i++) {
        heapify_up(arr, i);
    }

    // Ordena o array
    for (int i = 0; i < n; i++) {
        // Troca o último elemento com a raiz
        float temp = arr[0];
        arr[0] = arr[n - i - 1];
        arr[n - i - 1] = temp;

        // Ajusta o heap reduzido
        heapify_down(arr, n - i - 1, 0);
    }

    // Mostra o array ordenado na tela
    for (int i = 0; i < n; i++) {
        printf("%.2f\n", arr[i]);
    }

    free(arr);
    return 0;
}
