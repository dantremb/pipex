/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 20:49:17 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/16 12:22:01 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **envp)
{
	char	*envp_path;
	char	**fnct_path;
	int		i;

	envp_path = NULL;
	fnct_path = NULL;
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
	fnct_path = ft_split(envp_path, ':');
	free(envp_path);
	return (fnct_path);
}

char	*get_cmd_path(char **envp, char *cmd)
{
	char	**fcnt_path;
	char	*test_path;
	int		i;

	i = 0;
	fcnt_path = get_path(envp);
	while (fcnt_path[i])
	{
		test_path = ft_strjoin(fcnt_path[i], cmd);
		if (access(test_path, F_OK | X_OK) == 0)
		{
			free(fcnt_path);
			return (test_path);
		}
		free (test_path);
		i++;
	}
	return (NULL);
}

void	send_error(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}
