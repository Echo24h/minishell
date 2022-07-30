/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 00:31:56 by hvincent          #+#    #+#             */
/*   Updated: 2022/07/30 20:40:04 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*pwd(int ret)
{
	char	cwd[1024];
	char	*path;

	getcwd(cwd, sizeof(cwd));
	if (!ret)
		printf("%s\n", cwd);
	else
	{
		path = cwd;
		return (path);
	}
	return (NULL);
}
