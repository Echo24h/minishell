/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:39:24 by mbastard          #+#    #+#             */
/*   Updated: 2022/05/18 15:54:34 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**get_arg(char *cmd_line)
{
	char			**arg;

	arg = ft_split(cmd_line, ' ');
	return (arg);
}

static char	*get_cmd(char *cmd_line)
{
	char			*cmd;
	unsigned int	start;
	size_t			len;

	if (cmd_line[0] == ' ')
		start = 1;
	else
		start = 0;
	len = start;
	while(cmd_line[len] != ' ' && cmd_line[len] != '\0')
		len++;
	cmd = ft_substr(cmd_line, start, len);
	return (cmd);
}

void print_cmd(t_cmd *cmd)
{
	int	i;
	write(1, "cmd->cmd : ", 12);
	write(1, cmd->cmd, ft_strlen(cmd->cmd));
	write(1, "\n", 2);
	write(1, "cmd->arg : ", 12);
	i = 0;
	while (cmd->arg[i])
	{
		ft_putnbr(i);
		write(1, cmd->arg[i], ft_strlen(cmd->arg[i]));
		write(1, "-", 2);
		i++;
	}
	write(1, "\n", 2);

	write(1, "--cmd_init --\n", 14);
}

static t_cmd	*cmd_init(char *cmd_line)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->cmd = get_cmd(cmd_line);
	cmd->arg = get_arg(cmd_line);
	free(cmd_line);
	//print_cmd(cmd);
	return (cmd);
}

void	get_cmds(char *input, t_data *data)
{
	t_list	*cmds;
	char	**cmd_tab;
	int		i;

	cmd_tab = ft_split(input, '|');
	cmds = NULL;
	i = -1;
	while (cmd_tab[++i])
		ft_lstadd_back(&cmds, ft_lstnew(cmd_init(cmd_tab[i])));
	free(cmd_tab);
	data->cmds = cmds;
}
