/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 22:54:40 by mbastard          #+#    #+#             */
/*   Updated: 2022/05/08 15:26:13 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// write "exit\n" and exit the program
void	end()
{
	write(1, "exit\n", 5);
	exit(0);
}

int	main(void)
{
	char	*input;
	int		start;
	int		history_fd;
	t_data	data;

	start = 1;
	input = NULL;
	history_fd = open("tmp/history", O_RDWR | O_CREAT | O_APPEND, 0777);
	recover_history(history_fd);
	while (input || start--)
	{
		input = readline("minishell$ ");
		if (ft_strlen(input) > 0)
		{
			add_history(input);
			ft_putendl_fd(input, history_fd);
		}
		if (!ft_strncmp(input, "exit", 4))
			exit(0);
		get_cmds(input, &data);
		free(input);
		//print_cmds(data.cmds);
		exec(&data);
	}
	close(history_fd);
	return (0);
}

void	recover_history(int fd)
{
	int		i;
	size_t	len;
	char	*commands;
	char	**history;

	i = -1;
	len = 0;
	commands = get_next_line(fd);
	if (commands)
	{
		while (len != ft_strlen(commands))
		{
			len = ft_strlen(commands);
			commands = ft_strjoin(commands, get_next_line(fd));
		}
		write(1, "test\n", 5);
		history = ft_split(commands, '\n');
		if (history)
			while (history[++i])
				add_history(history[i]);
		free_tab(history);
	}
	free(commands);
}
