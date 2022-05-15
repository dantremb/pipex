/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 09:39:30 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/14 22:46:31 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main (int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	__pid_t	pid;
	int	tunnel[2];
	int 	intunnel;
	char	buffer[10];
	
	if (pipe(tunnel) == -1)
		return(1);
	pid = fork();
	if (pid == -1)
		printf("Fork Error\n");
	else if (pid == 0)
	{
		printf("Im the child writing in tube \n");
		dup2(tunnel[1], STDOUT_FILENO);
		dup2(intunnel, STDIN_FILENO);
		close(tunnel[0]);
		write(tunnel, "salut toi", 10);
		close(tunnel[1]);
		exit(EXIT_SUCCESS);
		
	}
	else if (pid > 0)
	{
		printf("Im the parent waiting\n");
		wait(&pid);
		printf("Im the parent reading the child tube\n");
		close(tunnel[1]);
		read(tunnel[0], buffer, 10);
		printf("parent read : %s\n", buffer);
		close(tunnel[0]);
		exit(EXIT_SUCCESS);
	}
}
