#include "ss_shell.h"

/**
 * main - create a super simple shell
 * @argc: argument count
 * @argv: argument vector
 * @envp: enviroment pointer
 * Return: always 0
 */

int main(int argc, __attribute__((unused)) char **argv, char ** envp)
{
	char *line; /* pointer to stored input line */
	char **tokens; /* array with the tokens in input line */
	int not_exit = 1; /* will control the exit condition */


	int stat_out;
	char **paths = NULL;
	char *new_path;

	/* size_t i; */
	pid_t cpid, w_out;
	int w_stat;
	struct stat stat_st;
	
	int prompt_n = 0;

	if (argc > 1)
	{
		fprintf(stderr, "sh: 0: arguments are not supported yet\n");
		exit(EXIT_FAILURE);
	}
	while (not_exit)
	{
		++prompt_n;
		printf("$$$$$ ");
		line = read_line();
		tokens = tokenize(line);
		if (tokens[0] != NULL && (not_exit = yes_exit(tokens[0])))
		{
			stat_out = stat(tokens[0], &stat_st);
			if (stat_out == -1 && tokens[0][0] != '/')
				new_path = find_file(tokens[0], envp);
			if (new_path != NULL)
			{
				tokens[0] = new_path;
				cpid = fork();
				if (cpid == -1)
				{
					perror("fork");
					free(line);
					free(tokens);
					if (!new_path && !paths)
					{
						free(new_path);
						free(paths);
					}
					exit(EXIT_FAILURE);
				}
				if (cpid != 0)
				{
					w_out = wait(&w_stat);
					if (w_out == -1)
					{
						perror("wait");
						free(line);
						free(tokens);
						if (!new_path && !paths)
						{
							free(new_path);
							free(paths);
						}
						exit(EXIT_FAILURE);
					}
				}
				if (cpid == 0 && execve(tokens[0], tokens, NULL) == -1)
				{
					perror("execve");
					free(line);
					free(tokens);
					if (!new_path && !paths)
					{
						free(new_path);
						free(paths);
					}
					exit(EXIT_FAILURE);
				}
				if (!new_path && !paths)
				{
					free(new_path);
					free(paths);
				}
			}
		}
		free(line);
		free(tokens);
	}

	return (0);
}
