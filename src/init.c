/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 20:28:17 by gborne            #+#    #+#             */
/*   Updated: 2022/07/30 20:29:03 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	init_env(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
			i++;
	data->export = (char **)ft_calloc((i + 2), sizeof(char *));
	data->envp = (char **)ft_calloc((i + 1), sizeof(char *));
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7) != 0)
		{
			data->export[i] = ft_strjoin2("declare -x ",
					insert_quotes_exp(envp[i], NULL), 0, 1);
			data->envp[i] = ft_strjoin2("", envp[i], 0, 0);
		}
		i++;
	}
	data->export[i] = ft_strdup("declare -x OLDPWD");
}

void	init(t_data *data, char **envp)
{
	init_env(data, envp);
	data->pipeline_status = ft_itoa(0);
	data->cmds = NULL;
	data->first_cmd = NULL;
}
