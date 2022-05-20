/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 20:49:17 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/20 10:40:38 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
		if (ft_strnstr(envp[i], "PTH=", ft_strlen(envp[i])))
		{
			envp_path = ft_strdup(envp[i]);
			if (!envp_path)
				send_error("path:envp");
			break ;
		}
		i++;
	}
	if (!envp_path)
		send_error("Env_path not found");
	fnct_path = ft_split(envp_path, 58);
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
			i = -1;
			while (fcnt_path[++i])
				free(fcnt_path[i]);
			free(fcnt_path);
			return (test_path);
		}
		free (test_path);
		i++;
	}
	i = -1;
	while (fcnt_path[++i])
		free(fcnt_path[i]);
	free(fcnt_path);
	return (NULL);
}

void	send_error(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}
