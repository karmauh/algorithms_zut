#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    int array[MAX_SIZE];
    int size;
} binary_heap;

void init(binary_heap* h);
void addElement(binary_heap* h, int data);
int maxElement(binary_heap* h);
void clear(binary_heap* h);
void up(binary_heap* h, int index);
void down(binary_heap* h, int index);

void init(binary_heap* h) {
    h->size = 0; //pusty
}

void addElement(binary_heap* h, int data) {
    if (h->size == MAX_SIZE) {
        return;
    }

    h->array[h->size] = data;
    h->size++;

    up(h, h->size - 1);
}

int maxElement(binary_heap* h) {
    if (h->size == 0) {
        return -1;
    }

    int max = h->array[0];

    h->array[0] = h->array[h->size - 1];
    h->size--;

    down(h, 0);

    return max;
}

void up(binary_heap* h, int index) {
    int parent = (index - 1) / 2;

    if (parent >= 0 && h->array[index] > h->array[parent]) {
        int temp = h->array[index];
        h->array[index] = h->array[parent];
        h->array[parent] = temp;

        up(h, parent);
    }
}

void down(binary_heap* h, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    int largest = index;
    if (left < h->size && h->array[left] > h->array[largest]) {
        largest = left;
    }
    if (right < h->size && h->array[right] > h->array[largest]) {
        largest = right;
    }

    if (largest != index) {
        int temp = h->array[index];
        h->array[index] = h->array[largest];
        h->array[largest] = temp;

        down(h, largest);
    }
}

void clear(binary_heap* h) {
    free(h->array);
    h->size = 0;
}


int main() {
    binary_heap h;
    init(&h);

    addElement(&h, 3);
    addElement(&h, 6);
    addElement(&h, 2);
    addElement(&h, 8);
    addElement(&h, 1);

    printf("%d\n", maxElement(&h));

    addElement(&h, 9);
    addElement(&h, 4);
    addElement(&h, 7);
    addElement(&h, 5);

    printf("%d\n", maxElement(&h));

    clear(&h);

    return 0;
}
