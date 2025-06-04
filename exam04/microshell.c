#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void ft_putstr_fd2(char *str, char *arg)
{
	while (*str)
		write(2, str++, 1);
	if (arg)
		while (*arg)
			write (2, arg++, 1);
	write(2, "\n", 1);
}

void fatal()
{
	write(2, "error: fatal\n", 14);
	exit(1);
}

void ft_execute(char **argv, int i, int tmp_fd, char **env)
{
	argv[i] = NULL;
	if (dup2(tmp_fd, 0) == -1 || close(tmp_fd) == -1)
		fatal();
	execve(argv[0], argv, env);
	ft_putstr_fd2("error: cannot execute ", argv[0]);
	exit(1);
}

int	main(int argc, char **argv, char **env)
{
	int i = 0;
	int tmp_fd = dup(0);
	int fd[2];
	(void)argc;

	if (tmp_fd == -1)
		fatal();
	while (argv[i] && argv[i + 1])
	{
		argv = &argv[i + 1];
		i = 0;
		while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
			i++;
		if (strcmp(argv[0], "cd") == 0)
		{
			if (i != 2)
				ft_putstr_fd2("error: cd: bad arguments", NULL);
			else if (chdir(argv[1]) != 0)
				ft_putstr_fd2("error: cd: cannot change directory to ", argv[1]);
		}
		else if (i != 0 && (argv[i] == NULL || strcmp(argv[i], ";") == 0))
		{
			pid_t pid = fork();
			if (pid == -1)
				fatal();
			if (pid == 0)
				ft_execute(argv, i, tmp_fd, env);
			else
			{
				if (close(tmp_fd) == -1)
					fatal();
				while (waitpid(-1, NULL, 2) != -1)
					;
				tmp_fd = dup(0);
				if (tmp_fd == -1)
					fatal();
			}
		}
		else if (i != 0 && strcmp(argv[i], "|") == 0)
		{
			if (pipe(fd) == -1)
				fatal();
			pid_t pid = fork();
			if (pid == -1)
				fatal();
			if (pid == 0)
			{
				if (dup2(fd[1], 1) == -1 || close(fd[1]) == -1 || close(fd[0]) == -1)
					fatal();
				ft_execute(argv, i, tmp_fd, env);
			}
			else
			{
				if (close(fd[1]) == -1 || close(tmp_fd) == -1)
					fatal();
				tmp_fd = fd[0];
			}
		}
	}
	if (close(tmp_fd) == -1)
		fatal();
	return (0);
}
