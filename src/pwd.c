/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 20:50:08 by gborne            #+#    #+#             */
/*   Updated: 2022/07/16 23:27:08 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	pwd(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->envp[++i])
		if (!ft_strncmp(cmd->envp[i], "PWD=", 4))
		{
			write(1, cmd->envp[i], ft_strlen(cmd->envp[i]));
			write(1, "\n", 1);
		}
}
