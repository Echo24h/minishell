/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:37:16 by gborne            #+#    #+#             */
/*   Updated: 2022/08/02 02:04:01 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Execute command and write OUT in fd[1] of pipe.
static void	exec_cmd(t_cmd *cmd)
{
	if (is_builtin(cmd))
		builtin(cmd);
	else
	{
		if (cmd->cmd == NULL)
			exit(0);
		bin(cmd);
	}
}

static void	process(pid_t pid, t_data *data, int *fd, int fd_tmp)
{
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
}

static void	exec_pipe(t_data *data)
{
	pid_t	pid;
	int		fd[2];
	int		fd_tmp;
	int		wstatus;

	fd_tmp = dup(0);
	while (data->cmds)
	{
		pipe(fd);
		pid = fork();
		process(pid, data, fd, fd_tmp);
		data->cmds = data->cmds->next;
	}
	close(fd_tmp);
	wstatus = 0;
	while (wait(&wstatus) > 0)
	{
		free(g_status);
		g_status = ft_itoa(WEXITSTATUS(wstatus));
	}
}

static void	exec_solo(t_cmd *cmd)
{
	if (is_builtin(cmd))
		builtin(cmd);
	else
		exec_pipe(cmd->data);
}

int	exec(t_data *data)
{
	if (data->cmds)
	{
		if (data->cmds->next)
			exec_pipe(data);
		else
			if (data->cmds->content)
				exec_solo(data->cmds->content);
	}
	else
		write(1, "Error : wrong input\n", 21);
	return (0);
}
