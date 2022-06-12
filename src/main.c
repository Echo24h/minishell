/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbastard <mbastard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 22:54:40 by mbastard          #+#    #+#             */
/*   Updated: 2022/06/12 19:15:19 by mbastard         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_data	data;

	manage_history(NULL);
	while (argv && argc)
	{
		input = readline(CYELLOW "minishell$ " RESET);
		if (ft_strlen(input) > 0)
			manage_history(input);
		if (!ft_strncmp(input, "exit", 5))
			quit("exit\n", 0, 0);
		if (ft_strlen(input) > 0)
		{
			get_cmds(input, &data);
			free(input);
			//print_cmds(data.cmds);
			exec(&data, envp);
			clear_data(&data);
		}
	}
	return (0);
}

void	quit(char *error_message, int error_code, int clean)
{
	if (clean >= 2)
		;
	if (error_message)
		ft_putstr_fd(error_message, 1);
	if (clean == 1)
		free(error_message);
	exit(error_code);
}
