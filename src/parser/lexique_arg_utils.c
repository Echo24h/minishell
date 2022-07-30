/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexique_arg_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:05:56 by gborne            #+#    #+#             */
/*   Updated: 2022/07/30 21:03:02 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	get_revquote(const char quote)
{
	char	revquote;

	revquote = '\"';
	if (quote == '\"')
		revquote = '\'';
	return (revquote);
}

// GET LEN FOR MALLOC
static int	len_subquote(char *str, char quote, char revquote, int quote_c)
{
	int	i;
	int	o;

	i = -1;
	o = 0;
	while (str[++i])
	{
		if (str[i] != quote)
		{
			if (str[i] == revquote && quote_c % 2 == 0)
			{
				i++;
				while (str[i] && str[i] != revquote)
				{
					o++;
					i++;
				}
			}
			else
				o++;
		}
		else
			quote_c++;
	}
	return (o);
}

// WRITE IN new[o] WHITH SAME BOUCLE
static char	*get_new(char *new, char *str,
	char quote, int quote_c)
{
	int		i;
	int		o;
	char	revquote;

	i = -1;
	o = -1;
	revquote = get_revquote(quote);
	while (str[++i])
	{
		if (str[i] != quote)
		{
			if (str[i] == revquote && quote_c % 2 == 0)
			{
				i++;
				while (str[i] && str[i] != revquote)
					new[++o] = str[i++];
			}
			else
				new[++o] = str[i];
		}
		else
			quote_c++;
	}
	new[++o] = '\0';
	return (new);
}

char	*subquote(char *str, char quote)
{
	int		len;
	char	revquote;
	char	*new;

	revquote = get_revquote(quote);
	len = len_subquote(str, quote, revquote, 0);
	if (len == 0)
		return (NULL);
	new = (char *)ft_calloc(len + 1, sizeof(char));
	new = get_new(new, str, quote, 0);
	if (str)
		free(str);
	return (new);
}

char	**add_arg(char **args, char *add)
{
	int		i;
	char	**new;

	i = 0;
	if (add == NULL)
		return (args);
	if (args)
	{
		while (args[i])
			i++;
		new = (char **)ft_calloc(i + 2, sizeof(char *));
		i = -1;
		while (args[++i])
			new[i] = args[i];
		free(args);
	}
	else
		new = (char **)ft_calloc(2, sizeof(char *));
	new[i] = add;
	new[i + 1] = NULL;
	return (new);
}
