/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 19:15:36 by gborne            #+#    #+#             */
/*   Updated: 2022/04/15 19:01:41 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_cmds(t_list *cmds)
{
	t_cmd	*cmd;
	int		i;

	i = 1;
	while (cmds)
	{
		cmd = cmds->content;
		printf("cmd %d = '%s'\n",i++, cmd->cmd);
		cmds = cmds->next;
	}
}
