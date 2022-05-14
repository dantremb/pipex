/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 09:39:30 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/14 11:48:50 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void get_function(char **envp)
{
	char	*envp_path = NULL;
	int		i;
	
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PiTH=", ft_strlen(envp[i])))
		{
			envp_path = ft_strdup(envp[i]);
			break ;
		}
		i++;
	}
	if (!envp_path)
		ft_putstr("\nNOT FOUND");
	else
	{
		ft_putstr(envp_path);
	}
}

int main (int argc, char **argv, char **envp)
{
	char *options[3] = {"tree", "-f", NULL};
	

	if (argc == 3)
		get_function(envp);
	else if (argc == 2)
		ft_putstr(argv[1]);
	else
		execve("/Users/dantremb/.brew/bin/tree", options, envp);
	
	return (0);
}
