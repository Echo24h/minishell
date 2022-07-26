/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 02:51:14 by gborne            #+#    #+#             */
/*   Updated: 2022/07/26 09:48:45 by gborne           ###   ########.fr       */
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
	int	simplequote;
	int	doublequote;
	int	i;

	simplequote = 0;
	doublequote = 0;
	i = -1;
	while (input[++i])
	{
		if (doublequote % 2 == 0 && input[i] == '\'')
			simplequote++;
		else if (simplequote % 2 == 0 && input[i] == '\"')
			doublequote++;
	}
	if (simplequote % 2 || doublequote % 2)
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
			if (error_quotes(input))
				write(1, "Error : wrong quotes\n", 22);
			else
			{
				manage_history(input);
				parser(input, &data);
				exec(&data);
				clear_data(&data);
			}
		}
	}
	return (0);
}
