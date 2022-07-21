/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 02:51:14 by gborne            #+#    #+#             */
/*   Updated: 2022/07/21 05:11:54 by gborne           ###   ########.fr       */
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

int	main(int argc __unused, char **arg __unused, char **envp)
{
	char	*input;
	t_data	data;

	init(&data, envp);
	manage_history(NULL);
	while (1)
	{
		input = readline(CYELLOW "minishell$ " RESET);
		if (!input)
			ft_exit();
		else if (ft_strlen(input))
		{
			manage_history(input);
			get_cmds(input, &data);
			exec(&data);
			clear_data(&data);
		}
	}
	return (0);
}
