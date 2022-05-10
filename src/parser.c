/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:39:24 by mbastard          #+#    #+#             */
/*   Updated: 2022/05/10 21:33:11 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_cmd	*cmd_init(char *cmd_line)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = cmd_line;
	return (cmd);
}

void	get_cmds(char *input, t_data *data)
{
	t_list	*cmds;
	char	**cmd_tab;
	int		i;

	cmd_tab = ft_split(input, '|');
	cmds = NULL;
	i = -1;
	while (cmd_tab[++i])
		ft_lstadd_back(&cmds, ft_lstnew(cmd_init(cmd_tab[i])));
	data->cmds = cmds;
}
