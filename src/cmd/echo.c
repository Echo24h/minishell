/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:26:25 by gborne            #+#    #+#             */
/*   Updated: 2022/08/01 19:06:29 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_newline(char *arg)
{
	int	i;

	i = 1;
	if (arg)
	{
		if (arg[0] && arg[0] == '-')
		{
			while(arg[i] && arg[i] == 'n')
			{
				i++;
				if (arg[i] == '\0')
					return (1);
			}
		}
	}
	return (0);
}

static int	get_newline(char **arg)
{
	int	newline;
	int	i;

	newline = 0;
	i = 1;
	while (is_newline(arg[i]))
	{
		newline++;
		i++;
	}
	return (newline);
}

void	echo(t_cmd *cmd)
{
	char	*str;
	int		i;
	int		newline;

	i = 1;
	newline = get_newline(cmd->arg);
	if (newline > 0)
		i += newline;
	if (cmd->arg[i])
	{
		str = ft_strdup(cmd->arg[i]);
		while (cmd->arg[++i])
		{
			str = ft_strjoin(str, " ");
			str = ft_strjoin(str, cmd->arg[i]);
		}
		if (newline == 0)
			str = ft_strjoin(str, "\n");
		write(1, str, ft_strlen(str));
		free(str);
	}
	else
		if (newline == 0)
			write(1, "\n", 2);
}
