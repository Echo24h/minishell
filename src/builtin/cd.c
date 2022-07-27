/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:08:10 by gborne            #+#    #+#             */
/*   Updated: 2022/07/27 15:20:31 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cd(t_cmd *cmd)
{
	printf("mmmm\n");
	if (cmd->arg[1] == NULL)
	{
		printf("pls\n");
		chdir("/");
	}
	else if (!access(cmd->arg[1], R_OK))
	{
		printf("arg: %s\n", cmd->arg[1]);
		chdir(cmd->arg[1]);
	}
	else if (cmd->arg[1][0] == '~')
		chdir("Users/[login]");
	else
		printf("Folder not found\n");
}
