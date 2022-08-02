/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:52:38 by gborne            #+#    #+#             */
/*   Updated: 2022/08/02 02:00:23 by gborne           ###   ########.fr       */
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
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->arg)
		free_tab(cmd->arg);
	if (cmd)
		free(cmd);
}

void	free_cmds(t_data *data)
{
	data->cmds = data->first_cmd;
	data->first_cmd = NULL;
	ft_lstclear(&data->cmds, &free_cmd);
	free(data->cmds);
}

void	free_data(t_data *data)
{
	free_cmds(data);
	free(g_status);
	free_tab(data->envp);
	free_tab(data->export);
}
