/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 20:49:17 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/15 15:33:23 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **get_path(char **envp)
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
	return (ft_split(envp_path, ':'));
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
			return(test_path);
		free (test_path);
		i++;
	}
	return(NULL);
}