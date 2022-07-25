/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexique_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:11:56 by gborne            #+#    #+#             */
/*   Updated: 2022/07/25 19:15:29 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


char	*ft_subchar(char *str, const char c)
{
	int		i;
	int		o;
	char	*new;

	i = -1;
	o = 0;
	while(str[++i])
		if (str[i] != c)
			o++;
	if (o == 0)
		return (NULL);
	new = (char *)ft_calloc(o + 1, sizeof(char));
	i = -1;
	o = 0;
	while(str[++i])
	{
		if (str[i] != c)
		{
			new[o] = str[i];
			o++;
		}
	}
	new[o] = '\0';
	if (str)
		free(str);
	return (new);
}

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
	int		i_tmp;
	char	**args;

	args = NULL;
	i_tmp = 0;
	i = -1;
	quote = 0;
	while(input[++i])
	{

		//printf("i=%d i_tmp=%d\n", i, i_tmp);
		if (input[i] == '\"')
		{
			while(input[i_tmp] == ' ')
				i_tmp++;
			quote = 1;
			i++;
			while (input[i])
			{
				//printf("i=%d quote=%d\n", i, quote);
				if (input[i] == '\"')
					quote++;
				if (input[i] == ' ' && quote % 2 == 0)
					break;
				i++;
			}
			args = add_arg(args, ft_subchar(ft_substr(input, i_tmp, i - i_tmp), '"'));
			i_tmp = i + 1;
		}
		else if (input[i] == '\'')
		{
			while(input[i_tmp] == ' ')
				i_tmp++;
			quote = 1;
			i++;
			while (input[i])
			{
				//printf("i=%d quote=%d\n", i, quote);
				if (input[i] == '\'')
					quote++;
				if (input[i] == ' ' && quote % 2 == 0)
					break;
				i++;
			}
			args = add_arg(args, ft_subchar(ft_substr(input, i_tmp, i - i_tmp), '\''));
			i_tmp = i + 1;
		}
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
	if (i != i_tmp && !ft_strchr("\' \"", input[i - 1]))
		args = add_arg(args, ft_substr(input, i_tmp, i - i_tmp));
	return (args);
}

char	**lexique_arg(const char *input)
{
    char **arg;

	arg = get_arg(input);
	int i = -1;
	while(arg[++i])
		printf("arg[%d]={%s}\n",i, arg[i]);
	exit(0);
    return (arg);
}
