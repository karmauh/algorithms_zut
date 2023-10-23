#include <stdio.h>
#include <windows.h>

int main(int argc, char** argv) {
    int ag = atoi(argv[1]);
    if (argc != 2) {
        printf("Zla ilosc argumentow");
        return 1;
    }

    for (int j = 0; j < strlen(argv[1]); j++) {
            if (!isdigit(argv[1][j])) {
                return 2;
            }
    }

    if (ag == 1 || ag == 2) {
        return 1;
    }

    if (ag < 1 || ag>13) {
        printf("Podaj wartosc z przedzialu od 1 do 13");
        return 3;
    }

    STARTUPINFOA s;
    PROCESS_INFORMATION p[2];

    char arg[50];
    memset(&s, 0, sizeof(s));
    memset(&p, 0, sizeof(p));
    s.cb = sizeof(s);

    DWORD back[2];
    DWORD pid[2];

    sprintf_s(arg, "zad3.exe %d", (ag - 1));
    CreateProcessA(NULL, arg, NULL, NULL, 0, 0, NULL, NULL, &s, p);
    sprintf_s(arg, "zad3.exe %d", (ag - 2));
    CreateProcessA(NULL, arg, NULL, NULL, 0, 0, NULL, NULL, &s, p + 1);

    for (int i = 0; i < 2; i++) {
        WaitForSingleObject(p[i].hProcess, INFINITE);
        pid[i] = p[i].dwProcessId;
        GetExitCodeProcess(p[i].hProcess, &back[i]);
    }

    CloseHandle(p[0].hProcess);
    CloseHandle(p[1].hProcess);

    fprintf(stdout, "%d\t%d\t  %d  %d\n", GetCurrentProcessId(), pid[0], ag - 1, back[0]);
    fprintf(stdout, "%d\t%d\t  %d  %d\n", GetCurrentProcessId(), pid[1], ag - 2, back[1]);
    fprintf(stdout, "%d\t             %d\n\n", GetCurrentProcessId(), back[0] + back[1]);

    return back[0] + back[1];
}
