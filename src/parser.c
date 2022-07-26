/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 02:51:03 by gborne            #+#    #+#             */
/*   Updated: 2022/07/26 08:48:21 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**get_arg(t_data *data, char *cmd_line)
{
	char			**arg;
	char			*line;

	line = lexique_var(data, cmd_line);
	arg = lexique_arg(line);
	//arg = ft_split(line, ' ');
	/*int i = -1;
	printf("cmd_line=%s\n", cmd_line);
	while (arg[++i])
	{
		printf("arg[%d]=%s-\n", i, arg[i]);
		printf("arg[%d]=%s-\n", i, arg[1]);
	}
	exit(0);*/
	return (arg);
}

static char	*get_cmd(char *cmd_line)
{
	char			*cmd;
	unsigned int	start;
	size_t			len;

	cmd = NULL;
	start = 0;
	while(cmd_line[start] == ' ')
		start++;
	len = start;
	while(cmd_line[len] != ' ' && cmd_line[len])
		len++;
	if (cmd_line[len] == ' ')
		cmd_line[len] = '\0';
	cmd = ft_substr(cmd_line, start, len);
	return (cmd);
}

static void	*cmd_init(char *cmd_line, t_data *data)
{
	t_cmd	*cmd;

	//printf("cmd_line=%s\n", cmd_line);
	cmd = malloc(sizeof(t_cmd));
	cmd->arg = get_arg(data, cmd_line);
	cmd->cmd = get_cmd(cmd->arg[0]);
	cmd->data = data;
	//free(cmd_line);
	//print_cmd(cmd);
	return ((void *)cmd);
}

void	parser(char *input, t_data *data)
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
	free(input);
	data->cmds = cmds;
}
