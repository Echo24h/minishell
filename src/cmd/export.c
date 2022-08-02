/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 00:31:47 by hvincent          #+#    #+#             */
/*   Updated: 2022/08/02 01:14:44 by gborne           ###   ########.fr       */
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

void	export_arg(t_cmd *cmd, int i)
{
	int	x;

	x = -1;
	if (check_if_equal(cmd->arg[i]) == 1)
		add_env_line(cmd, i);
	if (check_if_equal(cmd->arg[i]) != 2)
		add_exp_line(cmd, i);
	if (check_if_equal(cmd->arg[i]) == 2)
		while (cmd->data->export[++x])
			printf("export: %s\n", cmd->data->export[x]);
}

static int	check_arg(char *arg)
{
	int	i;

	i = 1;
	if (ft_isalpha(arg[0]) == 0)
		return (1);
	while (arg[i])
	{
		if (arg[i] == ' ' || arg[i] == '=')
			break ;
		if (ft_isalnum(arg[i]) == 0)
			return (1);
		i++;
	}
	return (0);
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
		i = 1;
		while (cmd->arg[i])
		{
			if (check_arg(cmd->arg[i]))
			{
				printf("Error : '%s': not a valid identifier\n", cmd->arg[i]);
				break ;
			}
			else
				export_arg(cmd, i);
			i++;
		}
	}
}
