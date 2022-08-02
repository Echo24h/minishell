/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexique_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 14:17:07 by gborne            #+#    #+#             */
/*   Updated: 2022/08/02 01:10:16 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cmd_count(char const *s, int simplequote, int doublequote)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] == '|')
			i++;
		if (s[i] != '|' && s[i])
			words++;
		while (s[i]
			&& (s[i] != '|' || simplequote % 2 == 1 || doublequote % 2 == 1))
		{
			if (doublequote % 2 == 0 && s[i] == '\'')
				simplequote++;
			else if (simplequote % 2 == 0 && s[i] == '\"')
				doublequote++;
			i++;
		}
	}
	return (words);
}

char	*split_part(char const *s)
{
	int		i;
	char	*cmd;
	int		simplequote;
	int		doublequote;

	simplequote = 0;
	doublequote = 0;
	i = 0;
	while (s[i]
		&& (s[i] != '|' || simplequote % 2 == 1 || doublequote % 2 == 1))
	{
		if (doublequote % 2 == 0 && s[i] == '\'')
			simplequote++;
		else if (simplequote % 2 == 0 && s[i] == '\"')
			doublequote++;
		i++;
	}
	cmd = malloc(sizeof(char) * (i + 1));
	if (!cmd)
		return (NULL);
	ft_strlcpy(cmd, s, i + 1);
	return (cmd);
}

static char	**split_pipe(char const *s)
{
	int		i;
	int		len;
	char	**cmd_tab;

	if (!s)
		return (NULL);
	len = cmd_count(s, 0, 0);
	if (len <= 0)
		return (NULL);
	cmd_tab = (char **)ft_calloc((len + 1), sizeof(char *));
	i = -1;
	while (++i < len)
	{
		while (*s == '|')
			s++;
		cmd_tab[i] = split_part(s);
		if (!cmd_tab[i])
		{
			free(cmd_tab);
			return (NULL);
		}
		s += ft_strlen(cmd_tab[i]);
	}
	cmd_tab[i] = 0;
	return (cmd_tab);
}

static int	check_pipe(const char *input, int simplequote, int doublequote)
{
	int	i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (input[i] == '|')
		return (1);
	while (input[i])
	{
		if (doublequote % 2 == 0 && input[i] == '\'')
			simplequote++;
		else if (simplequote % 2 == 0 && input[i] == '\"')
			doublequote++;
		if (input[i] == '|' && (simplequote % 2 == 0 || doublequote % 2 == 0))
		{
			i++;
			while (input[i] == ' ' || input[i] == '\t')
				i++;
			if (input[i] == '|' || input[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

char	**lexique_pipe(const char *input)
{
	char	**cmd_tab;

	if (check_pipe(input, 0, 0))
		return (NULL);
	cmd_tab = split_pipe(input);
	return (cmd_tab);
}
