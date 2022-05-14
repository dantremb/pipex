/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 09:39:30 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/14 12:54:04 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *get_path(char **envp)
{
	char	*envp_path = NULL;
	int		i;
	
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])))
		{
			envp_path = ft_strdup(envp[i]);
			break ;
		}
		i++;
	}
	return (envp_path);
}

char	*get_cmd_path(char *env_path, char *cmd)
{
	char	**fcnt_path;
	char	*test_path;
	int		i;
	
	i = 0;
	fcnt_path = ft_split(env_path, ':');
	while (fcnt_path[i])
	{
		test_path = ft_strjoin(fcnt_path[i], cmd);
		if (access(test_path, F_OK | X_OK) == 0)
			return(test_path);
		free (test_path);
		i++;
	}
	return(NULL);
}

int main (int argc, char **argv, char **envp)
{
	char *options[3] = {"tree", "-f", NULL};
	char *cmd = "/tree";

	if (argc == 3)
	{
		ft_putstr(get_cmd_path(get_path(envp), cmd));
	}
	else if (argc == 2)
		ft_putstr(argv[1]);
	else
		execve("/Users/dantremb/.brew/bin/tree", options, envp);
	
	return (0);
}
