/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 02:51:14 by gborne            #+#    #+#             */
/*   Updated: 2022/07/25 19:11:31 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	clear_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	free(cmd->cmd);
	free_tab(cmd->arg);
}

void	clear_data(t_data *data)
{
	ft_lstclear(&data->cmds, &clear_cmd);
	free(data->cmds);
}

int	error_quotes(const char *input)
{
	int	simple_quotes;
	int	double_quotes;
	int	i;

	simple_quotes = 0;
	double_quotes = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'')
			simple_quotes++;
		else if (input[i] == '\"')
			double_quotes++;
	}
	if (simple_quotes % 2 || double_quotes % 2)
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_data	data;

	(void)argv;
	(void)argc;
	init(&data, envp);
	manage_history(NULL);
	while (1)
	{
		input = readline(CYELLOW "minishell$ " RESET);
		if (!input)
			ft_exit();
		else if (ft_strlen(input))
		{
			//if (error_quotes(input))
			//	write(1, "Error\nWrong quotes\n", 20);
			manage_history(input);
			parser(input, &data);
			exec(&data);
			clear_data(&data);
		}
	}
	return (0);
}
