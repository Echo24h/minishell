/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 00:31:47 by hvincent          #+#    #+#             */
/*   Updated: 2022/08/01 20:07:30 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_quotes(int j)
{
	if (j == 1)
		return (3);
	else
		return (1);
}

char	*insert_quotes_exp(const char *s1, char *s2)
{
	int	k;
	int	j;
	int	equal;

	k = 0;
	j = check_if_equal(s1);
	equal = 0;
	s2 = malloc(sizeof(char) * (ft_strlen(s1) + is_quotes(j)));
	while (*s1)
	{
		if (*s1 == '=' && equal == 0)
		{
			s2[k] = '=';
			s2[++k] = '"';
			equal++;
		}
		else
			s2[k] = *s1;
		k++;
		s1++;
	}
	if (j)
		s2[k++] = '"';
	s2[k] = '\0';
	return (s2);
}

void	add_exp_line(t_cmd *cmd)
{
	int		i;
	int		add;
	char	*tmp;
	char	*arg_cpy;

	i = -1;
	tmp = (char *)ft_calloc(1, sizeof(char));
	add = 1;
	arg_cpy = ft_strjoin2("declare -x ",
			insert_quotes_exp(cmd->arg[1], NULL), 0, 1);
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

void	add_env_line(t_cmd *cmd)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = (char *)ft_calloc(1, sizeof(char));
	while (cmd->data->envp[++i])
		if (do_not_replace(cmd->data->envp[i], cmd->arg[1]))
		tmp = ft_strjoin_2(tmp, cmd->data->envp[i]);
	tmp = ft_strjoin_2(tmp, cmd->arg[1]);
	free_tab(cmd->data->envp);
	cmd->data->envp = ft_split(tmp, '\n');
	free(tmp);
}

void	export(t_cmd *cmd)
{
	int		i;

	i = -1;
	if (cmd->arg[1] == NULL)
		while (cmd->data->export[++i])
			printf("%s\n", cmd->data->export[i]);
	else
	{
		if (check_if_equal(cmd->arg[1]) == 1)
			add_env_line(cmd);
		if (check_if_equal(cmd->arg[1]) != 2)
			add_exp_line(cmd);
		if (check_if_equal(cmd->arg[1]) == 2)
			while (cmd->data->export[++i])
				printf("export: %s\n", cmd->data->export[i]);
	}
}
