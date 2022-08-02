/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 00:31:56 by hvincent          #+#    #+#             */
/*   Updated: 2022/08/02 01:13:46 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_if_equal(const char *s)
{
	int	i;

	i = -1;
	if (*s)
	{
		while (s[++i])
		{
			if (s[i] == '=')
				return (1);
			else if (s[i] == '$')
				return (2);
		}
	}
	return (0);
}

int	arg_is_diff(const char *cpy, const char *arg)
{
	int	i;

	i = 0;
	while (cpy[i])
	{
		if (arg[i] == '\0' && cpy[i] != '=')
			return (1);
		if (cpy[i] == '=')
			if (arg[i] == '=' || arg[i] == '\0')
				return (0);
		if (cpy[i] != '=' && arg[i] == '=')
			return (1);
		if (cpy[i] != arg[i])
			return (1);
		i++;
	}
	if (arg[i] == '=')
		return (2);
	else if (arg[i] == '\0')
		return (0);
	return (1);
}

void	add_exp_line(t_cmd *cmd, int x)
{
	int		i;
	int		add;
	char	*tmp;
	char	*arg_cpy;

	i = -1;
	tmp = (char *)ft_calloc(1, sizeof(char));
	add = 1;
	arg_cpy = ft_strjoin2("declare -x ",
			insert_quotes_exp(cmd->arg[x], NULL), 0, 1);
	while (cmd->data->export[++i])
	{
		if (arg_is_diff(arg_cpy, cmd->data->export[i]) == 2)
			add = 0;
		if (arg_is_diff(arg_cpy, cmd->data->export[i]))
			tmp = ft_strjoin_2(tmp, cmd->data->export[i]);
	}
	if (add)
		tmp = ft_strjoin_2(tmp, arg_cpy);
	free(arg_cpy);
	free_tab(cmd->data->export);
	cmd->data->export = ft_split(tmp, '\n');
	free(tmp);
}

void	add_env_line(t_cmd *cmd, int x)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = (char *)ft_calloc(1, sizeof(char));
	while (cmd->data->envp[++i])
		if (do_not_replace(cmd->data->envp[i], cmd->arg[x]))
		tmp = ft_strjoin_2(tmp, cmd->data->envp[i]);
	tmp = ft_strjoin_2(tmp, cmd->arg[x]);
	free_tab(cmd->data->envp);
	cmd->data->envp = ft_split(tmp, '\n');
	free(tmp);
}
