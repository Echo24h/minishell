/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbastard <mbastard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 13:15:51 by mbastard          #+#    #+#             */
/*   Updated: 2022/06/12 13:16:17 by mbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void manage_history(char *input)
{
	int		history_fd;

	history_fd = open("tmp/history", O_RDWR | O_CREAT | O_APPEND, 0777);
	add_history(input);
	ft_putendl_fd(input, history_fd);
	close(history_fd);
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