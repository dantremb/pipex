/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 09:39:30 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/16 23:11:21 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			send_error("pipe error");
		pid = fork();
		if (pid == -1)
			send_error("fork error");
		else if (pid == 0)
			child(argv, envp, fd);
		parent(argv, envp, fd);
	}
	else
		send_error("bad argument");
	return (0);
}

void	command(char *argv, char **envp)
{
	char	**options;
	char	*path;
	char	*cmd;
	int		i;

	options = ft_split(argv, 32);
	cmd = ft_strjoin("/", options[0]);
	path = get_cmd_path(envp, cmd);
	if (!path | !cmd | !options)
	{
		i = -1;
		while (options[++i])
			free (options[i]);
		free (options);
		free (cmd);
		send_error("command not found");
	}
	i = execve(path, options, envp);
	if (i == -1)
		send_error("Execute error");
}

void	child(char **argv, char **envp, int *fd)
{
	int		file1;

	file1 = open(argv[1], O_RDONLY, 0644);
	if (file1 == -1)
		send_error("file1 not found");
	dup2(fd[1], STDOUT_FILENO);
	dup2(file1, STDIN_FILENO);
	close(fd[0]);
	command(argv[2], envp);
}

void	parent(char **argv, char **envp, int *fd)
{
	int		file2;

	file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file2 == -1)
		send_error("file2 not found");
	dup2(fd[0], STDIN_FILENO);
	dup2(file2, STDOUT_FILENO);
	close(fd[1]);
	command(argv[3], envp);
}
