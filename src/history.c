/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 02:51:21 by gborne            #+#    #+#             */
/*   Updated: 2022/07/29 19:00:04 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//recover history from the history file
static void	recover_history(int fd)
{
	size_t	i;
	char	*cmd;
	char	*cmds;

	i = -1;
	cmds = NULL;
	cmd = get_next_line(fd);
	if (cmd)
	{
		cmds = ft_strjoin2(cmds, cmd, 1, 1);
		while (cmd)
		{
			cmd = get_next_line(fd);
			cmds = ft_strjoin2(cmds, cmd, 1, 1);
		}
		while (++i < ft_strlen(cmds))
		{
			cmd = ft_subdup(&cmds[i], '\n');
			i += ft_sublen(&cmds[i], '\n');
			add_history(cmd);
			free(cmd);
		}
		free(cmds);
	}
}

void	manage_history(char *cmd)
{
	int			fd;

	fd = open("tmp/history", O_RDWR | O_CREAT | O_APPEND, 0777);
	if (!cmd)
		recover_history(fd);
	else
	{
		add_history(cmd);
		ft_putendl_fd(cmd, fd);
	}
	close(fd);
}
