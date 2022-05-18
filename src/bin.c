/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:26:25 by gborne            #+#    #+#             */
/*   Updated: 2022/05/18 16:29:44 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	bin(t_cmd *cmd)
{
	char	*path;

	path = malloc(sizeof(char) * 10);
	ft_strlcpy(path, "/usr/bin/", 10);
	path = ft_strjoin(path, cmd->cmd);
	if (execve(path, cmd->arg, cmd->envp) == -1)
		write(1, "Error bin.c file not found\n", 28);
}
