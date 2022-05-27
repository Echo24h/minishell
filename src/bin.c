/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:26:25 by gborne            #+#    #+#             */
/*   Updated: 2022/05/27 19:15:52 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	bin(t_cmd *cmd)
{
	char	*path;

	path = ft_strdup("/usr/bin/");
	path = ft_strjoin(path, cmd->cmd);
	if (execve(path, cmd->arg, cmd->envp) == -1)
		write(1, "Error bin.c file not found\n", 28);
}
