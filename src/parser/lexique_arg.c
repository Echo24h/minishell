/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexique_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:11:56 by gborne            #+#    #+#             */
/*   Updated: 2022/07/27 15:20:03 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


char	*subquote(char *str, char c)
{
	int		i;
	int		o;
	int		quote;
	char	revquote;
	char	*new;

	i = -1;
	o = 0;
	quote = 0;
	revquote = '\"';
	if (c == '\"')
		revquote = '\'';
	// FIRST READ FOR MALLOC "o"
	while(str[++i])
	{
		if (str[i] != c)
		{
			if (str[i] == revquote && quote % 2 == 0)
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
			quote++;
	}
	if (o == 0)
		return (NULL);
	new = (char *)ft_calloc(o + 1, sizeof(char));
	i = -1;
	o = 0;
	// WRITE IN new[o] WHITH SAME BOUCLE
	while(str[++i])
	{
		if (str[i] != c)
		{
			if (str[i] == revquote && quote % 2 == 0)
			{
				i++;
				while (str[i] && str[i] != revquote)
				{
					new[o] = str[i];
					o++;
					i++;
				}
			}
			else
			{
				new[o] = str[i];
				o++;
			}
		}
		else
			quote++;
	}
	new[o] = '\0';
	if (str)
		free(str);
	return (new);
}

// Add the string 'add' in existant **args or create this, and return the new '**args'
char	**add_arg(char **args, char *add)
{
	int		i;
	char	**new;

	i = 0;
	if (add == NULL || add[0] == '\0')
		return (args);
	if (args)
	{
		while(args[i])
			i++;
		new = (char **)ft_calloc(i + 2, sizeof(char *));
		i = -1;
		while(args[++i])
			new[i] = args[i];
		free(args);
	}
	else
		new = (char **)ft_calloc(2, sizeof(char *));
	new[i] = add;
	new[i + 1] = NULL;
	//printf("add=%s i=%d\n", add, i);
	i = -1;
	//while(new[++i])
	//	printf("new[%d]=%s\n", i, new[i]);
	return (new);
}

char	**get_arg(const char *input)
{
	int		i;
	int		quote;
	int		revquote;
	int		i_tmp;
	char	**args;

	args = NULL;
	i_tmp = 0;
	i = -1;
	quote = 0;
	revquote = 0;
	while(input[++i])
	{

		//printf("i=%d i_tmp=%d\n", i, i_tmp);

		// MANAGE DOUBLE QUOTES

		if (input[i] == '\"')
		{
			while(input[i_tmp] == ' ')
				i_tmp++;
			quote = 1;
			revquote = 0;
			i++;
			while (input[i])
			{
				//printf("i=%d quote=%d\n", i, quote);
				if (quote % 2 == 0 && input[i] == '\'')
					revquote++;
				else if (revquote % 2 == 0 && input[i] == '\"')
					quote++;
				else if (input[i] == ' ' && quote % 2 == 0 && revquote % 2 == 0)
					break;
				i++;
			}
			args = add_arg(args, subquote(ft_substr(input, i_tmp, i - i_tmp), '"'));
			i_tmp = i + 1;
		}

		// MANAGE SIMPLE QUOTE

		else if (input[i] == '\'')
		{
			while(input[i_tmp] == ' ')
				i_tmp++;
			quote = 1;
			revquote = 0;
			i++;
			while (input[i])
			{
				//printf("i=%d quote=%d\n", i, quote);
				if (quote % 2 == 0 && input[i] == '\"')
					revquote++;
				else if (revquote % 2 == 0 && input[i] == '\'')
					quote++;
				else if (input[i] == ' ' && quote % 2 == 0  && revquote % 2 == 0)
					break;
				i++;
			}
			args = add_arg(args, subquote(ft_substr(input, i_tmp, i - i_tmp), '\''));
			i_tmp = i + 1;
		}
		// MANAGE SPACE

		else if (input[i] == ' ' && i != i_tmp && !ft_strchr("\' \"", input[i - 1]))
		{
			while(input[i_tmp] == ' ')
				i_tmp++;
			args = add_arg(args, ft_substr(input, i_tmp, i - i_tmp));
			while(input[i] == ' ')
				i++;
			i_tmp = i;
			i--;
		}
	}

	// END OF INPUT
	if (i != i_tmp && !ft_strchr("\' \"", input[i - 1]))
		args = add_arg(args, ft_substr(input, i_tmp, i - i_tmp));
	return (args);
}

char	**lexique_arg(const char *input)
{
    char **arg;

	arg = get_arg(input);

	/*
	int i = -1;
	while(arg[++i])
		printf("arg[%d]={%s}\n",i, arg[i]);
	exit(0);*/
    return (arg);
}
