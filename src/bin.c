/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:26:25 by gborne            #+#    #+#             */
/*   Updated: 2022/07/16 20:33:24 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


static char **get_path_list(char **envp)
{
	int		i;
	char	**path_list;
	char	*tmp;

	i = -1;
	path_list = NULL;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_list = ft_split(envp[i], ':');
			tmp = path_list[0];
			path_list[0] = ft_substr(path_list[0], 5, ft_strlen(path_list[0]));
			free(tmp);
			break ;
		}
	}
	return (path_list);
}

void	bin(t_cmd *cmd)
{
	char	*path;
	char	**path_list;
	int		i;

	path_list = get_path_list(cmd->envp);
	i = -1;
	if(path_list == NULL)
		write(1, "Error 'path_list'\n", 19);
	else
	{
		while (path_list[++i])
		{
			path = ft_strdup(path_list[i]);
			path = ft_strjoin(path, "/");
			path = ft_strjoin(path, cmd->cmd);
			execve(path, cmd->arg, cmd->envp);
		}
		write(1, "Error bin.c file not found\n", 28);
	}
	free_tab(path_list);
}
