/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 02:51:03 by gborne            #+#    #+#             */
/*   Updated: 2022/07/30 17:41:13 by gborne           ###   ########.fr       */
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

static void	*cmd_init(const char *cmd_line, t_data *data)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->arg = get_arg(data, cmd_line);
	cmd->cmd = get_cmd(cmd->arg[0]);
	cmd->data = data;
	return ((void *)cmd);
}

void	parse_cmds(const char *input, t_data *data)
{
	t_list	*cmds;
	char	**cmd_tab;
	int		i;

	cmd_tab = lexique_pipe(input);
	i = -1;
	cmds = NULL;
	while (cmd_tab[++i])
		ft_lstadd_back(&cmds, ft_lstnew(cmd_init(cmd_tab[i], data)));
	free_tab(cmd_tab);
	data->cmds = cmds;
}
