/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbastard <mbastard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:39:24 by mbastard          #+#    #+#             */
/*   Updated: 2022/06/12 20:23:46 by mbastard         ###   ########.fr       */
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

	start = 0;
	if (cmd_line[0] == ' ')
		start++;
	len = start;
	while(cmd_line[len] != ' ' && cmd_line[len])
		len++;
	cmd = ft_substr(cmd_line, start, len);
	return (cmd);
}

static void	*cmd_init(char *cmd_line, t_data *data)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->cmd = get_cmd(cmd_line);
	cmd->arg = get_arg(cmd_line);
	cmd->data = data;
	//free(cmd_line);
	//print_cmd(cmd);
	return ((void *)cmd);
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
		ft_lstadd_back(&cmds, ft_lstnew(cmd_init(cmd_tab[i], data)));
	free_tab(cmd_tab);
	free(input);
	data->cmds = cmds;
}
