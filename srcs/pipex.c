/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 09:39:30 by dantremb          #+#    #+#             */
/*   Updated: 2023/02/08 16:27:45 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			send_error("Pipe Error");
		pid = fork();
		if (pid == -1)
			send_error("Fork Error");
		else if (pid == 0)
			child(argv, envp, fd);
		parent(argv, envp, fd);
	}
	else
		send_error("Bad Argument");
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
		send_error("command:path");
	}
	i = execve(path, options, envp);
	if (i == -1)
		send_error("command:execve");
}

void	child(char **argv, char **envp, int *fd)
{
	int		file1;

	file1 = open(argv[1], O_RDONLY, 0644);
	if (file1 == -1)
		send_error("child:infile");
	dup2(fd[1], STDOUT_FILENO);
	dup2(file1, STDIN_FILENO);
	close(fd[0]);
	command(argv[2], envp);
	close(file1);
}

void	parent(char **argv, char **envp, int *fd)
{
	int		file2;

	file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file2 == -1)
		send_error("parent:outfile");
	dup2(fd[0], STDIN_FILENO);
	dup2(file2, STDOUT_FILENO);
	close(fd[1]);
	command(argv[3], envp);
	close(file2);
}
