/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 09:39:30 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/15 15:37:36 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char **argv, char **envp, int *fd)
{
	int		file1;
	char	**options;
	char	*path;
	
	options = ft_split(argv[2], 32);
	path = get_cmd_path(envp, ft_strjoin("/", options[0]));
	file1 = open(argv[1], O_RDONLY, 0777);
	dup2(fd[1], STDOUT_FILENO);
	dup2(file1, STDIN_FILENO);;
	close(fd[0]);
	execve(path, options, envp);
}

void	parent(char **argv, char **envp, int *fd)
{
	int		file2;
	char	**options;
	char	*path;
	
	wait(NULL);
	options = ft_split(argv[3], 32);
	path = get_cmd_path(envp, ft_strjoin("/", options[0]));
	file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(fd[0], STDIN_FILENO);
	dup2(file2, STDOUT_FILENO);
	close(fd[1]);
	execve(path, options, envp);
}

int main (int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		fd[2];
	if (argc == 5)
	{
		if (pipe(fd) == -1)
			return(1);
		pid = fork();
		if (pid == 0)
			child(argv, envp, fd);
		else
			parent(argv, envp, fd);
	}
	else
		write(1, "Invalid Argument", 17);
	return (0);
}
