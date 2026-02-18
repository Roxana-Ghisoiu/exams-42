/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roxana <rghisoiu@student.42luxembourg.lu>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:44:29 by roxana            #+#    #+#             */
/*   Updated: 2025/05/15 11:00:58 by roxana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void	err(char  *str)
{
	while (*str)
		write(2, str++, 1);
}

int	do_cd(char **argv, int i)
{
	if(i != 2)
	{
		err("error: cd: bad arguments\n");
		return (1);
	}
	if(chdir(argv[1]) == -1)
	{
		err("error: cd: cannot change directory to ");
		err(argv[1]);
		err("\n");
		return(1);
	}
	return(0);
}

void	set_pipe(int has_pipe, int *fd, int end)
{
	if(has_pipe && (dup2(fd[end], end) == -1 || close (fd[0]) == -1 || close (fd[1]) == -1))
		err("error: fatal\n"), exit (1);
}

int	exec(char **argv, int i, char **envp)
{
	int	has_pipe;
	int 	fd[2];
	int	pid;
	int	status;

	has_pipe = argv[i] && !strcmp(argv[i], "|");
	if(!has_pipe && !strcmp(*argv, "cd"))
		return(do_cd(argv, i));
	if(has_pipe && pipe(fd) == -1)
	{
		err("error: fatal\n");
		exit(1);
	}
	pid = fork();
	if(pid == -1)
	{
		err("error: fatal\n");
		exit(1);
	}
	if(pid == 0)
	{
		argv[i] = 0;
		set_pipe(has_pipe, fd, 1);
		if(!strcmp(*argv, "cd"))
			return(do_cd(argv, i));
		execve(*argv, argv, envp);
		err("error: cannot execute "), err(*argv), err("\n"), exit(1);
	}
	waitpid(pid, &status, 0);
	set_pipe(has_pipe, fd, 0);
	return WIFEXITED(status) && WEXITSTATUS(status);
}

int	main(int argc, char **argv, char **envp)
{
	int	status, i;

	i = 0;
	status = 0;

	if(argc < 2)
		return(0);
	while(argv[i])
	{
		argv = argv + (i + 1);
		i = 0;
		while(argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
			i++;
		if(i)
			status = exec(argv, i, envp);
	}
	return (status);
}
