/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 02:51:14 by gborne            #+#    #+#             */
/*   Updated: 2022/08/01 18:15:59 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// check quotes and return (0) if is valid or return (1)
int	check_quotes(const char *input)
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

void	minishell(t_data *data)
{
	char	*input;

	input = readline(CYELLOW "minishell$ " RESET);
	if (!input)
	{
		free_data(data);
		ft_exit();
	}
	else if (ft_strlen(input))
	{
		if (check_quotes(input))
			write(1, "Error : wrong quotes\n", 22);
		else
		{
			manage_history(input);
			parse_cmds(input, data);
			exec(data);
			free_cmds(data);
		}
	}
	free(input);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	(void)argc;
	init(&data, envp);
	manage_history(NULL);
	signal(SIGINT, &signal_controller);
	while (1)
		minishell(&data);
	return (0);
}
