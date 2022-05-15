/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 09:39:30 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/14 20:49:54 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main (int argc, char **argv, char **envp)
{
	char *options[3] = {"tree", "-f", NULL};
	char *cmd = "ls";

	if (argc == 3)
		ft_putstr(get_cmd_path(envp, ft_strjoin("/", cmd)));
	else if (argc == 2)
		ft_putstr(argv[1]);
	else
		execve(get_cmd_path(envp, ft_strjoin("/", cmd)), options, envp);
	return (0);
}
