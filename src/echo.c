/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:26:25 by gborne            #+#    #+#             */
/*   Updated: 2022/05/27 20:38:06 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	echo(t_cmd *cmd, int *fd)
{
	char	*str;
	int		i;

	i = 1;
	if (cmd->arg[i])
	{
		str = cmd->arg[i];
		while (cmd->arg[++i])
		{
			str = ft_strjoin(str, " ");
			str = ft_strjoin(str, cmd->arg[i]);
		}
		str = ft_strjoin(str, "\n");
		write(fd[1], str, ft_strlen(str));
		free(str);
	}
}
