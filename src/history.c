/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbastard <mbastard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 13:15:51 by mbastard          #+#    #+#             */
/*   Updated: 2022/06/12 20:01:44 by mbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief recover history from the history file
 * 
 * @param fd history file descriptor
 */
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
	int			history_fd;

	history_fd = open("tmp/history", O_RDWR | O_CREAT | O_APPEND, 0777);
	if (!cmd)
		recover_history(history_fd);
	else
	{
		add_history(cmd);
		ft_putendl_fd(cmd, history_fd);
	}
	close(history_fd);
}
