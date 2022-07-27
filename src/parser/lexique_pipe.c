/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexique_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 14:17:07 by gborne            #+#    #+#             */
/*   Updated: 2022/07/27 15:20:11 by gborne           ###   ########.fr       */
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
		while (s[i] &&
			( s[i] != '|' || simplequote % 2 == 1 || doublequote % 2 == 1))
		{
			  //MANAGE QUOTES
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

	int simplequote = 0;
	int doublequote = 0;
	i = 0;
	while (s[i] &&
	( s[i] != '|' || simplequote % 2 == 1 || doublequote % 2 == 1))
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
	cmd_tab = malloc(sizeof(char *) * (len + 1));
	if (!cmd_tab)
		return (NULL);
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

char	**lexique_pipe(const char *input)
{

	char	**cmd_tab;

	cmd_tab = split_pipe(input);
	return (cmd_tab);
}
