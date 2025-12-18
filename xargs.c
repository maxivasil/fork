#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#ifndef NARGS
#define NARGS 4
#endif

void
execute_command(char *args[], int count)
{
	args[count + 1] = NULL;

	pid_t pid = fork();
	if (pid == 0) {
		execvp(args[0], args);
		perror("execvp");
		exit(EXIT_FAILURE);
	} else if (pid > 0) {
		wait(NULL);
	} else {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	for (int i = 1; i <= count; i++) {
		free(args[i]);
	}
}

int
main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Uso: %s <comando>\n", argv[0]);
		return EXIT_FAILURE;
	}

	char *args[NARGS + 2];
	args[0] = argv[1];

	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int count = 0;

	while ((nread = getline(&line, &len, stdin)) != -1) {
		line[nread - 1] = '\0';
		args[count + 1] = strdup(line);
		if (args[count + 1] == NULL) {
			perror("strdup");
			free(line);
			return EXIT_FAILURE;
		}

		count++;

		if (count == NARGS) {
			execute_command(args, count);
			count = 0;
		}
	}

	if (count > 0) {
		execute_command(args, count);
	}

	free(line);
	return EXIT_SUCCESS;
}
