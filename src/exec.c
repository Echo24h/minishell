/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:37:16 by gborne            #+#    #+#             */
/*   Updated: 2022/06/12 17:23:14 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**add_out(char **arg, char *out)
{
	int		i;
	char	**new;

	i = -1;
	while(arg[++i])
		;
	new = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (arg[++i])
	{
		new[i] = arg[i];
		free(arg[i]);
	}
	new[i] = out;
	return (new);
}

// Execute command and write OUT in fd[1] of pipe.
void	exec_cmd(t_cmd *cmd, int *fd, char **envp, char *out)
{
	pid_t	pid;

	cmd->envp = envp;

	if (ft_strnstr("echo env pwd cd", cmd->cmd, 16))
	{
		builtin(cmd, fd);
	}
	else
	{
		pid = fork();
		if (out)
			cmd->arg = add_out(cmd->arg, out);
		if (pid == 0)
		{
			close(fd[0]);
			dup2(fd[1], 1);
			if (cmd->cmd == NULL)
				exit(0);
			bin(cmd);
			clear_data(cmd->data);
			exit(0);
		}
	}
}

char	*get_out(char *buff)
{
	int		i;
	char	*out;

	i = 0;
	out = NULL;
	while (buff[i])
		i++;
	if (i > 0)
	{
		out = ft_calloc(i + 1, sizeof(char));
		i = -1;
		while(buff[++i])
			out[i] = buff[i];
	}
	return out;
}

int	exec(t_data *data, char **envp)
{
	int		fd[2];
	char	buff[4096];
	char	*out;

	out = NULL;
	while (data->cmds)
	{
		ft_bzero(buff, 4096);
		pipe(fd);
		exec_cmd(data->cmds->content, fd, envp, out);
		read(fd[0], &buff, 4096);
		if (out)
			free(out);
		out = get_out(buff);
		data->cmds = data->cmds->next;
		close(fd[0]);
		close(fd[1]);
	}
	if (out)
	{
		write(1, out, ft_strlen(out));
		free(out);
	}
	return (0);
}
