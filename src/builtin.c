/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:26:25 by gborne            #+#    #+#             */
/*   Updated: 2022/07/21 05:06:40 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin(t_cmd *cmd)
{
	// ft_printf("size: %d, cmd: '%s'", ft_strlen(cmd->cmd), cmd->cmd);
	if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		echo(cmd);
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
		env(cmd);
	else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
		pwd(cmd);
	else if (ft_strncmp(cmd->cmd, "export", 7) == 0)
		export(cmd);
	else if (ft_strncmp(cmd->cmd, "cd", 2) == 0)
		cd(cmd);
	else if (ft_strncmp(cmd->cmd, "exit", 4) == 0)
		ft_exit();
	else
		write(1, cmd->cmd, ft_strlen(cmd->cmd) + 1);
	return (0);
}

