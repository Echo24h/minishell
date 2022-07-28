/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:26:25 by gborne            #+#    #+#             */
/*   Updated: 2022/07/28 03:36:35 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd, "echo") == 0 && ft_strlen(cmd->cmd) == 4)
		return (1);
	else if (ft_strcmp(cmd->cmd, "env") == 0 && ft_strlen(cmd->cmd) == 3)
		return (1);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0 && ft_strlen(cmd->cmd) == 3)
		return (1);
	else if (ft_strcmp(cmd->cmd, "export") == 0 && ft_strlen(cmd->cmd) == 6)
		return (1);
	else if (ft_strcmp(cmd->cmd, "cd") == 0 && ft_strlen(cmd->cmd) == 2)
		return (1);
	else if (ft_strcmp(cmd->cmd, "exit") == 0 && ft_strlen(cmd->cmd) == 4)
		return (1);
	else if (ft_strcmp(cmd->cmd, "unset") == 0 && ft_strlen(cmd->cmd) == 5)
		return (1);
	else
		return (0);
}

int	builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		echo(cmd);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		env(cmd);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		pwd(0);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		export(cmd);
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		cd(cmd);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		ft_exit();
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		unset(cmd);
	return (0);
}

