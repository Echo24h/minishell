/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 20:50:08 by gborne            #+#    #+#             */
/*   Updated: 2022/07/30 16:05:32 by gborne           ###   ########.fr       */
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
