/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:26:25 by gborne            #+#    #+#             */
/*   Updated: 2022/07/30 20:36:23 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_newline(char *arg)
{
	if (arg && ft_strcmp(arg, "-n") == 0)
		return (0);
	else
		return (1);
}

void	echo(t_cmd *cmd)
{
	char	*str;
	int		i;
	int		newline;

	i = 1;
	newline = is_newline(cmd->arg[1]);
	if (newline == 0)
		i++;
	if (cmd->arg[i])
	{
		str = ft_strdup(cmd->arg[i]);
		while (cmd->arg[++i])
		{
			str = ft_strjoin(str, " ");
			str = ft_strjoin(str, cmd->arg[i]);
		}
		if (newline)
			str = ft_strjoin(str, "\n");
		write(1, str, ft_strlen(str));
		free(str);
	}
	else
		if (newline)
			write(1, "\n", 2);
}
