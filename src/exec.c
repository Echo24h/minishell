/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:37:16 by gborne            #+#    #+#             */
/*   Updated: 2022/07/18 04:34:33 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Execute command and write OUT in fd[1] of pipe.
void	exec_cmd(t_cmd *cmd, char **envp)
{
	cmd->envp = envp;
	if (ft_strnstr("echo env pwd cd", cmd->cmd, 16))
		builtin(cmd);
	else
	{
		if (cmd->cmd == NULL)
			exit(0);
		bin(cmd);
	}
}

int	exec(t_data *data, char **envp)
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
			exec_cmd(data->cmds->content, envp);
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
	return (0);
}
