/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:37:16 by gborne            #+#    #+#             */
/*   Updated: 2022/05/08 15:27:34 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_builtin()
{
	return (1);
}

char	*builtin(t_cmd *cmd)
{
	//char	*out;
	//out = ;
	//out = ftstrjoin(out, "Command: ");
	//out = ft_strjoin(out, cmd->cmd);
	//out = ft_strjoin(out, "\nOut of command: coucou\n");
	return (cmd->cmd);
}

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
		write(fd[1], out, ft_strlen(out));
		free(out);
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
	out = malloc(i + 1);
	i = 0;
	while(buff[i])
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
	pipe(fd);
	while (data->cmds)
	{
		exec_cmd(data->cmds->content, fd);
		read(fd[0], &buff, 4096);
		out = get_out(buff);
		data->cmds = data->cmds->next;
	}
	close(fd[0]);
	close(fd[1]);
	write(1, out, ft_strlen(out));
	free(out);
	return (0);
}
