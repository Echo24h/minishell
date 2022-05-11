/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:37:16 by gborne            #+#    #+#             */
/*   Updated: 2022/05/11 13:30:53 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Execute command and write OUT in fd[1] of pipe.
void	exec_cmd(t_cmd *cmd, int *fd)
{
	pid_t	pid;
	char	*out;
	out = NULL;
	pid = fork();

	if (pid == 0)
	{
		close(fd[0]);
		if (cmd->cmd == NULL)
			exit(0);
		if (is_builtin())
			out = builtin(cmd);
		else
			out = bin(cmd);
		write(fd[1], out, ft_strlen(out) + 1);
		close(fd[1]);
		free(out);
		exit(0);
	}
}

char	*get_out(char *buff)
{
	int		i;
	char	*out;

	i = 0;
	while (buff[i] != '\0')
		i++;
	out = malloc(i + 1);
	i = 0;
	while(buff[i] != '\0')
	{
		out[i] = buff[i];
		i++;
	}
	out[i] = '\0';
	return out;
}

int	exec(t_data *data)
{
	int		fd[2];
	char	buff[4096];
	char	*out;

	out = NULL;

	while (data->cmds)
	{
		pipe(fd);
		exec_cmd(data->cmds->content, fd);
		read(fd[0], &buff, 4096);
		out = get_out(buff);
		write(1, out, ft_strlen(out));
		write(1, "\n", 2);
		data->cmds = data->cmds->next;
		close(fd[0]);
		close(fd[1]);
	}
	free(out);
	return (0);
}
