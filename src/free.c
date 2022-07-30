/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:52:38 by gborne            #+#    #+#             */
/*   Updated: 2022/07/30 17:35:05 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab[i]);
	free(tab);
}

void	free_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	free(cmd->cmd);
	free_tab(cmd->arg);
	free(cmd);
}

void	free_cmds(t_data *data)
{
	ft_lstclear(&data->cmds, &free_cmd);
	free(data->cmds);
}

void	free_data(t_data *data)
{
	free_cmds(data);
	free(data->pipeline_status);
	free_tab(data->envp);
	free_tab(data->export);
}
