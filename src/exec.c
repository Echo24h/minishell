/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:37:16 by gborne            #+#    #+#             */
/*   Updated: 2022/07/21 05:05:56 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Execute command and write OUT in fd[1] of pipe.
void	exec_cmd(t_cmd *cmd)
{
	if (ft_strnstr("echo env pwd cd export exit", cmd->cmd, 28))
		builtin(cmd);
	else
	{
		if (cmd->cmd == NULL)
			exit(0);
		bin(cmd);
	}
}

static void	exec_pipe(t_data *data)
{
	pid_t	pid;
	int		fd[2];
	int		fd_tmp;
	int		i;

	i = 0;
	fd_tmp = dup(0);
	while (data->cmds)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{	
			close(fd[0]);
			dup2(fd_tmp, 0);
			close(fd_tmp);
			if (data->cmds->next)
				dup2(fd[1], 1);
			close(fd[1]);
			exec_cmd(data->cmds->content);
			exit(0);
		}	
		else
		{
			close(fd[1]);
			if (data->cmds->next)
			{
				close(fd_tmp);
				fd_tmp = dup(fd[0]);
			}
			close(fd[0]);
		}
		data->cmds = data->cmds->next;
		i++;
	}
	close(fd_tmp);
	while (waitpid(-1, 0, 0) > 0)
				;
}

static void	exec_solo(t_cmd *cmd)
{
	if (ft_strnstr("echo env pwd cd export exit", cmd->cmd, 28))
		builtin(cmd);
	else
		exec_pipe(cmd->data);
}

int	exec(t_data *data)
{
	if (data->cmds->next)
		exec_pipe(data);
	else
		if (data->cmds->content)
			exec_solo(data->cmds->content);
	return (0);
}
