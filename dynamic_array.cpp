#include <stdio.h>
#include <iostream>
#include <time.h>
#include <QDebug>
#include <QTime>

struct Darray {
    int **tab;
    int length;

    void createArray(int size) {
        tab = static_cast<int**>(malloc(static_cast<unsigned long long>(size) * sizeof(int*)));
        length = size;
        for (int i = 0; i < size; i++)
            tab[i] = new int(i * 2);
    }

    void removeElement(int index) {
        *tab[index] = *tab[length - 1];
        free(tab[length - 1]);
        length--;
    }
};

struct Struktura {
    int randomKey;
    float total;
    char randomChar;
};

Struktura** allocArray(int N) {
    struct Struktura** tab = static_cast<struct Struktura**>(malloc(static_cast<unsigned long long>(N) * sizeof(struct s*)));
    struct Darray array;
    array.createArray(10001, -1000);

    for (int i = 0; i < N; i++) {
        tab[i] = static_cast<struct Struktura*>(malloc(sizeof(struct Struktura)));

        int index = (rand() % (array.length + 1));
        tab[i]->randomKey = *array.tab[index];

        array.removeElement(index);
        tab[i]->randomChar = static_cast<char>((rand() % 40) + 60);
        tab[i]->total = 101 + i;
    }

    for (int i = 0; i < array.length - 1; i++)
        free(array.tab[i]);

    free(array.tab);

    return tab;
}

int findAndCountElementOfChar(Struktura** tab, char X, int size) {
    int count = 0;
    for (int i = 0; i < size - 1; i++)
        if (tab[i]->randomChar == X)
            count++;

    return count;
}

void printStruct(Struktura* structure, int counter) {
    qDebug() << "--------------------------------------------------------";
    qDebug() << "Obiekt nr " << counter << " losowy klucz:" << structure->randomKey << " losowy znak:" << structure->randomChar << " float(1000+id)" << structure->total;
}

void bubbleSort(Struktura** tab, int size) {
    bool swap = false;
    for (int j = 0; j < size - 1; j++) {
        for (int i = 0; i < size - 1 - j; i++) {
            auto swap1 = [](Struktura* pointer1, Struktura* pointer2)
            {Struktura temp = *pointer1; *pointer1 = *pointer2; *pointer2 = temp; return;};

            if (tab[i]->randomKey < tab[i + 1]->randomKey) {
                swap1(tab[i], tab[i + 1]);
                swap = true;
            }
        }

        if (!swap)
            return;
    }
}

void freeStruct(Struktura** tab, int size) {
    for (int i = 0; i < size - 1; i++)
        free(tab[i]);

    free(tab);
}

bool mejn() {
    QTime t;
    t.start();

    int N = 0;
    char X = 0;
    FILE* fp = fopen("dTablica.txt", "r");

    if (!fp)
        return false;

    fscanf(fp, "%d %c", &N, &X);
    fclose(fp);

    srand(uint(t.secsTo(QTime(23, 59))));
    Struktura** tab = allocArray(N);
    bubbleSort(tab, N);
    int count = findElementOfChar(tab, X, N);

    ///PRINTS
    ///
    qDebug() << "Uplynelo: " << t.elapsed() << "[ms]";
    qDebug() << "Wyswietlone top 20:";
    for (int i = 0; i < 20; i++) {
        printStruct(tab[i], i + 1);
    }

    qDebug() << "Ilosc obiektow ze znakiem " << X << " jest " << count;
    freeStruct(tab, N);

    qDebug() << "Koniec";
    qDebug() << "Czas jaki uplyna: " << t.elapsed() << "[ms]";

    return true;
}
