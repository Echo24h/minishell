/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 00:31:47 by hvincent          #+#    #+#             */
/*   Updated: 2022/07/28 05:51:26 by gborne           ###   ########.fr       */
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

char	*insert_quotes_exp(const char *s1, char *s2)
{
	int	k;
	int	j;
	int	equal;

	k = 0;
	j = check_if_equal(s1);
	equal = 0;
	if (j == 1)
		s2 = malloc(sizeof(char) * (ft_strlen(s1) + 3));
	else
		s2 = malloc(sizeof(char) * (ft_strlen(s1) + 1));
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
	//printf("%s\n %s\n", s1, s2);
	return (s2);
}

void	add_exp_line(t_cmd *cmd)
{
	int		i;
	char	*tmp;
	char	*arg_cpy;

	i = -1;
	tmp = NULL;
	arg_cpy = ft_strjoin2("declare -x ", insert_quotes_exp(cmd->arg[1], NULL), 0, 1);
	while (cmd->data->export[++i])
		if (ft_strncmp(cmd->data->export[i], arg_cpy, ft_strlen(arg_cpy)) != 0 && ft_strlen(arg_cpy) > ft_strlen("declare -x "))
			tmp = ft_strjoin_2(tmp, cmd->data->export[i]);
	tmp = ft_strjoin_2(tmp, arg_cpy);
	free(arg_cpy);
	free_tab(cmd->data->export);
	cmd->data->export = ft_split(tmp, '\n');
}

void	add_env_line(t_cmd *cmd)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (cmd->data->envp[++i])
		if (do_not_replace(cmd->data->envp[i], cmd->arg[1]))
		tmp = ft_strjoin_2(tmp, cmd->data->envp[i]);
	tmp = ft_strjoin_2(tmp, cmd->arg[1]);
	free_tab(cmd->data->envp);
	cmd->data->envp = ft_split(tmp, '\n');
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
