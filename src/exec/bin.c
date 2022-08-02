/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:26:25 by gborne            #+#    #+#             */
/*   Updated: 2022/08/01 23:46:47 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**get_path_list(char **envp)
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
			if (path_list == NULL)
				return (NULL);
			tmp = path_list[0];
			if (ft_strlen(path_list[0]) > 5)
				path_list[0] = ft_substr(path_list[0], 5,
						ft_strlen(path_list[0]));
			else
				path_list[0] = NULL;
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

	path_list = get_path_list(cmd->data->envp);
	i = -1;
	execve(cmd->cmd, cmd->arg, cmd->data->envp);
	if (path_list == NULL)
		write(1, "Error : path not found\n", 24);
	else
	{
		while (path_list[++i])
		{
			path = ft_strdup(path_list[i]);
			path = ft_strjoin(path, "/");
			path = ft_strjoin(path, cmd->cmd);
			execve(path, cmd->arg, cmd->data->envp);
			free(path);
		}
		write(1, "Error : ", 9);
		write(1, cmd->cmd, ft_strlen(cmd->cmd));
		write(1, " command not found\n", 20);
		free_tab(path_list);
	}
	exit(127);
}
