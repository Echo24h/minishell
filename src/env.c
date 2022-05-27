/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:26:25 by gborne            #+#    #+#             */
/*   Updated: 2022/05/27 20:43:19 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	env(t_cmd *cmd, int *fd)
{
	int		i;
	char	*str;

	i = -1;
	str = ft_calloc(1, sizeof(char));
	while (cmd->envp[++i])
	{
		str = ft_strjoin(str, cmd->envp[i]);
		str = ft_strjoin(str, "\n");
	}
	write(fd[1], str, ft_strlen(str));
	free(str);
}
