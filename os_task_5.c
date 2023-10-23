#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>

HANDLE mutex;
double leibniz = 0;

DWORD WINAPI leibnizPI(LPVOID LP) {
    double suma = 0;
    int* arg = (int*)LP;
    DWORD tID = GetCurrentThreadId();
    printf("Thread #%lu size=%d first=%d\n", tID, arg[1], arg[0]);

    for(int i = arg[0]; i < arg[0]+arg[1]; i++) {
        suma += pow(-1, i) / (2 * i + 1);
    }

    WaitForSingleObject(mutex, INFINITE);
    leibniz += suma;
    ReleaseMutex(mutex);
}

int main(int argc, char** argv) {
    int w = atoi(argv[2]);
    int it = atoi(argv[1]);
    double leibniz2 = 0;

    if(argc != 3) {
        printf("zla ilosc argumentow");
        return 1;
    }

    for(int j = 0; j < strlen(argv[1]); j++) {
        if(!isdigit(argv[1][j]))
            return 2;
    }

    if(it < 1 || it > 1000000000)
        return 0;
    if(w < 1 || w > 100)
        return 0;
    if(it < w)
        return 0;

    mutex = CreateMutex(NULL, FALSE, NULL);
    if(mutex == NULL)
        return 1;

    clock_t start = clock();
    HANDLE threads[w];
    for(int i = 0; i < w; i++) {
        int* arg2 = (int*)malloc(2 * sizeof(int));
        arg2[0] = i * ((it - 1) / w);
        arg2[1] = (i == (w-1))?((it-1) / w) + (it - 1) % w + 1:((it - 1) / w);
        threads[i] = CreateThread(NULL, 0, leibnizPI, arg2, 0, NULL);

        if(threads[i] == NULL)
            return 1;
    }

    WaitForMultipleObjects(w, threads, TRUE, INFINITE);
    clock_t stop = clock();
    double temp = stop - start;
    printf("w/Threads: PI=%.20lf time=%fs\n", leibniz * 4, temp/CLOCKS_PER_SEC);
    clock_t start2 = clock();

    for(int i = 0; i < it; i++)
        leibniz2 += pow(-1, i) / (2 * i + 1);

    clock_t stop2 = clock();
    double temp2 = stop2 - start2;
    printf("w/Threads: PI=%.20lf time=%fs\n", leibniz2 * 4, temp2/CLOCKS_PER_SEC);

    CloseHandle(mutex);

    return 0;
}
