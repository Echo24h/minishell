/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexique_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:11:56 by gborne            #+#    #+#             */
/*   Updated: 2022/07/30 16:17:14 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**add_quotes(char **args, const char *input, int *i,
		const char quote)
{
	char	quotes[2];
	int		quote_c[2];

	quotes[0] = quote;
	quotes[1] = get_revquote(quote);
	quote_c[0] = 1;
	quote_c[1] = 0;
	while (input[i[0]] == ' ')
		i[0]++;
	i[1]++;
	while (input[i[1]])
	{
		if (quote_c[0] % 2 == 0 && input[i[1]] == quotes[1])
			quote_c[1]++;
		else if (quote_c[1] % 2 == 0 && input[i[1]] == quotes[0])
			quote_c[0]++;
		else if (input[i[1]] == ' ' && quote_c[0] % 2 == 0
			&& quote_c[1] % 2 == 0)
			break ;
		i[1]++;
	}
	args = add_arg(args, subquote(ft_substr(input, i[0],
					i[1] - i[0]), quotes[0]));
	i[0] = i[1] + 1;
	return (args);
}

static char	**add_frontspace(char **args, const char *input, int *i)
{
	while (input[i[0]] == ' ')
		i[0]++;
	args = add_arg(args, ft_substr(input, i[0], i[1] - i[0]));
	while (input[i[1]] == ' ')
		i[1]++;
	i[0] = i[1];
	i[1]--;
	return (args);
}

char	**get_arg(const char *input)
{
	int		*i;
	char	**args;

	args = NULL;
	i = ft_calloc(2, sizeof(int));
	while (input[i[1]])
	{
		if (input[i[1]] == '\"')
			args = add_quotes(args, input, i, '\"');
		else if (input[i[1]] == '\'')
			args = add_quotes(args, input, i, '\'');
		else if (input[i[1]] == ' ' && i[1] != i[0]
			&& !ft_strchr("\' \"", input[i[1] - 1]))
			args = add_frontspace(args, input, i);
		if(input[i[1]])
			i[1]++;
	}
	if (i[1] != i[0] && !ft_strchr("\' \"", input[i[1] - 1]))
		args = add_arg(args, ft_substr(input, i[0], i[1] - i[0]));
	free(i);
	return (args);
}

char	**lexique_arg(const char *input)
{
	char	**arg;

	arg = get_arg(input);
	return (arg);
}
