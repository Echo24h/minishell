/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:37:16 by gborne            #+#    #+#             */
/*   Updated: 2022/05/18 16:22:34 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Execute command and write OUT in fd[1] of pipe.
void	exec_cmd(t_cmd *cmd, int *fd, char **envp)
{
	pid_t	pid;
	pid = fork();

	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		if (cmd->cmd == NULL)
			exit(0);
		cmd->envp = envp;
		if (is_builtin(cmd))
			builtin(cmd);
		else
			bin(cmd);
		exit(0);
	}
}

char	*get_out(char *buff)
{
	int		i;
	char	*out;

	i = 0;
	while (buff[i])
		i++;
	if (i > 0)
		out = malloc(i + 1);
	i = 0;
	while(buff[i])
	{
		out[i] = buff[i];
		i++;
	}
	if (i > 0)
		out[i] = '\0';
	else
		return NULL;
	return out;
}

int	exec(t_data *data, char **envp)
{
	int		fd[2];
	char	buff[4096];
	char	*out;
	int		i;

	out = NULL;

	while (data->cmds)
	{
		pipe(fd);
		exec_cmd(data->cmds->content, fd, envp);
		read(fd[0], &buff, 4096);
		if (out)
			free(out);
		out = get_out(buff);
		data->cmds = data->cmds->next;
		close(fd[0]);
		close(fd[1]);
		i = -1;
		while (buff[++i])
			buff[i] = 0;
	}
	if (out)
	{
		write(1, out, ft_strlen(out));
		free(out);
	}
	return (0);
}
