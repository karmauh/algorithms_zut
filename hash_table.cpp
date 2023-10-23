#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000

struct Node {
    char* key;
    char* value;
    struct Node* next;
};

struct HashTable {
    struct Node* table[SIZE];
};

void initHashTable(struct HashTable* ht);
void addToHashTable(struct HashTable* ht, char* key, char* value);
char* getFromHashTable(struct HashTable* ht, char* key);
void removeFromHashTable(struct HashTable* ht, char* key);
void clearHashTable(struct HashTable* ht);
int numIndices(struct HashTable* ht);


void initHashTable(struct HashTable* ht) {
    int i;

    for (i = 0; i < SIZE; i++) {
        ht->table[i] = NULL;
    }
}

int hashFunc(int key) {
    return key % SIZE;
}

void addToHashTable(struct HashTable* ht, char* key, char* value) {
    int hash = hashFunc(key);

    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->value = value;
    node->next = NULL;

    if (ht->table[hash] == NULL) {
        ht->table[hash] = node;
    }
    else {
        struct Node* current = ht->table[hash];
        while (current->next != NULL) {
            current = current->next;
        }

        current->next = node;
    }

    //rozszerzenie i przemiszanie 
    int newSize = SIZE * 2;
    struct Node* newTable[newSize];

    for (int i = 0; i < SIZE; i++) {
        struct Node* current = ht->table[i];

        while (current != NULL) {
            int newHash = hashFunc(current->key) % newSize;
            newTable[newHash] = current;
            current = current->next;
        }
    }

    free(ht->table);

    ht->table = newTable;
    ht->size = newSize;
}

char* getFromHashTable(struct HashTable* ht, char* key) {
    int hash = hashFunc(key);

    struct Node* current = ht->table[hash];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }

    return NULL;
}

void removeFromHashTable(struct HashTable* ht, char* key) {
    int hash = hashFunc(key);

    struct Node* current = ht->table[hash];
    struct Node* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                ht->table[hash] = current->next;
            }
            else {
                prev->next = current->next;
            }
            free(current);

            break;
        }
        
        prev = current;
        current = current->next;
    }
}

void clearHashTable(struct HashTable* ht) {
    for (int i = 0; i < SIZE; i++) {
        Node* current = ht->table[i];

        while (current != NULL) {
            Node* temp = current;
            current = current->next;

            free(temp);
        }

        ht->current[i] = NULL;
    }
}

int numIndices(struct HashTable* ht) {
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        if (ht->table[i] != NULL) {
            count++;
        }
    }

    return count;
}


int main() {
    struct HashTable ht;
    initHashTable(&ht);

    addToHashTable(&ht, "test", "111222333");
    addToHashTable(&ht, "test2", "444555666");


    printf("ilosc indeksow w tablicy: %s\n", numIndices(&ht));

    clearHashTable(&ht);
    printf("ilosc indeksow w tablicy: %s\n", numIndices(&ht));

    return 0;
}
