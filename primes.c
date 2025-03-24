#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void
sieve(int left_pipe[2])
{
	close(left_pipe[1]);
	int p;
	ssize_t bytes_read = read(left_pipe[0], &p, sizeof(int));
	
	if (bytes_read == 0)
	{
		close(left_pipe[0]);
		exit(EXIT_SUCCESS);
	} else if (bytes_read == -1) 
	{
		perror("read");
		close(left_pipe[0]);
		exit(EXIT_FAILURE);
	}

	printf("primo %d\n", p);
	
	int right_pipe[2];
	if (pipe(right_pipe) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		close(left_pipe[0]);
		close(right_pipe[1]);
		sieve(right_pipe);
	} else
	{
		close(right_pipe[0]);
		int n;
		while (read(left_pipe[0], &n, sizeof(int)) > 0)
		{
			if (n % p != 0)
			{
				if (write(right_pipe[1], &n, sizeof(int)) == -1)
				{
					perror("write");
					exit(EXIT_FAILURE);
				}
			}
		}
		close(left_pipe[0]);
		close(right_pipe[1]);
		wait(NULL);
		exit(EXIT_SUCCESS);
	}
}

int
main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Uso: %s <n>\n", argv[0]);
		return EXIT_FAILURE;
	}

	int n = atoi(argv[1]);
	if (n < 2)
	{
		fprintf(stderr, "El número debe ser mayor o igual a 2\n");
		return EXIT_FAILURE;
	}

	int pipefd[2];
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return EXIT_FAILURE;
	}

	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return EXIT_FAILURE;
	}

	if (pid == 0)
	{
		sieve(pipefd);
	} else 
	{
		close(pipefd[0]);
		for (int i = 2; i <= n; i++)
		{
			if (write(pipefd[1], &i, sizeof(int)) == -1)
			{
				perror("write");
				return EXIT_FAILURE;
			}
		}
		close(pipefd[1]);
		wait(NULL);
	}

	return EXIT_SUCCESS;
}
