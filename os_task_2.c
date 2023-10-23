#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "%s\n", "Brak argumentu lub zla ich ilosc! KOD BLEDU 1");
		return 1;
	}

	int value = *argv[1];
	if (value < 48 || value > 57) {
		fprintf(stderr, "%s\n", "Podany argument nie jest liczba naturalna! KOD BLEDU 2");
		return 2;
	}

	sscanf(argv[1], "%d", &value);
	if (value < 1 || value>13) {
		printf("%s\n", argv[1]);
		fprintf(stderr, "%s\n", "Podany argument nie jest z zakresu 1 - 13! KOD BLEDU 3");
		return 3;
	}

	int value2;
	sscanf(argv[1], "%d", &value2);

	if (value2 < 3) return 1;

	int chil_1 = value2 - 1, chil_2 = value2 - 2, status_1, status_2;
	char temp[4], temp2[4];

	sprintf(temp, "%d", chil_1);
	sprintf(temp2, "%d", chil_2);

	char* tab[] = {argv[0], temp, NULL};
	char* tab_2[] = {argv[0], temp2, NULL};


	pid_t c1_pid, c2_pid;
	(c1_pid = fork()) && (c2_pid = fork());

	if (c1_pid == 0)
		execvp(tab[0], tab);
	else if (c2_pid == 0)
		execvp(tab[0], tab_2);
	else {
		int exit_status_1, exit_status_2;

		waitpid(c1_pid, &status_1, 0);
		waitpid(c2_pid, &status_2, 0);

		if (WIFEXITED(status_1) && WIFEXITED(status_2)) {
			exit_status_1 = WEXITSTATUS(status_1);
			exit_status_2 = WEXITSTATUS(status_2);
			printf("%d %d %d %d\n", getpid(), c1_pid, chil_1, exit_status_1);
						printf("%d %d %d %d\n", getpid(), c2_pid, chil_2, exit_status_2);
			printf("%d        %d\n\n", getpid(), exit_status_1 + exit_status_2);
		}

		return exit_status_1 + exit_status_2;
	}
	
	return 0;
}
