/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 00:31:56 by hvincent          #+#    #+#             */
/*   Updated: 2022/07/28 03:23:29 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	do_not_replace(char *s, char *s2)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_subdup(s2, '=');
	if (ft_strnstr(s, tmp, ft_strlen(s) + 1) == NULL)
		i++;
	return (i);
}

char	*cd_pwd(int envp)
{
	char	*tmp;

	tmp = NULL;
	if (!envp)
	{
		tmp = ft_strjoin2("declare -x PWD=", pwd(1), 0, 0);
		tmp = ft_strjoin2("", insert_quotes_exp(tmp, NULL), 0, 0);
	}
	else if (envp == 1)
		tmp = ft_strjoin2("PWD=", pwd(1), 0, 0);
	return (tmp);
}

void	handle_exp_cd(t_cmd *cmd)
{
	int		i;
	char	*tmp;
	char	**cpy;

	i = -1;
	cpy = cmd->data->export;
	tmp = NULL;
	while (cpy[++i])
	{
		if (ft_strncmp(cpy[i], "declare -x PWD=", 15) != 0
			&& !(ft_strncmp(cpy[i], "declare -x OLDPWD\0", 18) == 0 || ft_strncmp(cpy[i], "declare -x OLDPWD=", 18) == 0))
		{
			tmp = ft_strjoin_2(tmp, cpy[i]);
		}
	}
	tmp = ft_strjoin_2(tmp, cd_pwd(0));
	i = -1;
	while (cmd->data->envp[++i])
		if (ft_strncmp(cmd->data->envp[i], "PWD=", 4) == 0)
			tmp = ft_strjoin_2(tmp, ft_strjoin_2("declare -x OLD", insert_quotes_exp(cmd->data->envp[i], NULL)));
	free_tab(cmd->data->export);
	cmd->data->export = ft_split(tmp, '\n');
	free(tmp);
}
