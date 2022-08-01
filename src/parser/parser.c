/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 02:51:03 by gborne            #+#    #+#             */
/*   Updated: 2022/08/01 19:14:37 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**get_arg(t_data *data, const char *cmd_line)
{
	char			**arg;
	char			*line;

	line = lexique_var(data, cmd_line);
	arg = lexique_arg(line);
	free(line);
	return (arg);
}

static char	*get_cmd(char *cmd_line)
{
	char			*cmd;
	unsigned int	start;
	size_t			len;

	cmd = NULL;
	start = 0;
	while (cmd_line[start] == ' ')
		start++;
	len = start;
	while (cmd_line[len] != ' ' && cmd_line[len])
		len++;
	cmd = ft_substr(cmd_line, start, len);
	return (cmd);
}

static t_cmd	*cmd_init(const char *cmd_line, t_data *data)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->arg = get_arg(data, cmd_line);
	if (cmd->arg)
		cmd->cmd = get_cmd(cmd->arg[0]);
	cmd->data = data;
	return (cmd);
}

void	parse_cmds(const char *input, t_data *data)
{
	t_list	*cmds;
	t_cmd	*tmp;
	char	**cmd_tab;
	int		i;

	cmd_tab = lexique_pipe(input);
	i = -1;
	cmds = NULL;
	tmp = NULL;
	while (cmd_tab && cmd_tab[++i])
	{
		if (!(cmd_tab[i][0] == '\0'
			|| (cmd_tab[i][0] == ' ' && cmd_tab[i][1] == '\0')))
		{
			tmp = cmd_init(cmd_tab[i], data);
			if (tmp)
				ft_lstadd_back(&cmds, ft_lstnew((void *)tmp));
		}
	}
	if (cmd_tab)
		free_tab(cmd_tab);
	data->cmds = cmds;
	data->first_cmd = cmds;
}
