/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexique_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:18:55 by gborne            #+#    #+#             */
/*   Updated: 2022/07/30 16:13:51 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*add_part(char *dst, const char *src, int start, int end)
{
	char	*new;

	new = (char *)ft_calloc(ft_strlen(dst) + (end - start) + 1, sizeof(char));
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, dst, ft_strlen(dst) + 1);
	ft_strlcat(new, src + start, ft_strlen(new) + end - start + 1);
	if (dst)
		free(dst);
	return (new);
}

static char	*add_var(t_data *data, char *dst, int id_var)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	if (id_var == -2)
		dst = add_part(dst, data->pipeline_status, 0,
				ft_strlen(data->pipeline_status));
	else
	{
		while (data->export[id_var][i] && data->export[id_var][i] != '=')
			i++;
		if (data->export[id_var][i] == '=')
		{
			start = i + 1;
			while (data->export[id_var][i])
				i++;
			if (i != start)
				dst = add_part(dst, data->export[id_var], start,
						ft_strlen(data->export[id_var]));
		}
	}
	return (dst);
}

static char	*manage_var(t_data *data, char *new, const char *line, int *i)
{
	int		start;
	char	*var;

	if (i[1] > 0)
		new = add_part(new, line, i[0], i[1]);
	start = i[1] + 1;
	if (line[i[1] + 1] == '?')
	{
		new = add_var(data, new, -2);
		i[1]++;
		i[0] = i[1] + 1;
	}
	else
	{
		while (ft_isalnum(line[++i[1]]))
			;
		var = ft_substr(line, start, i[1] - start);
		var = ft_strjoin(var, "=");
		if (id_var(data, var) != -1)
			new = add_var(data, new, id_var(data, var));
		free(var);
		i[0] = i[1];
		i[1]--;
	}
	return (new);
}

static char	*replace_var_env(t_data *data, char *line)
{
	int		*i;
	char	*new;
	int		*quotes;

	i = (int *)ft_calloc(2, sizeof(int));
	quotes = (int *)ft_calloc(2, sizeof(int));
	new = (char *)ft_calloc(1, sizeof(char));
	while (line[i[1]])
	{
		if (quotes[1] % 2 == 0 && line[i[1]] == '\'')
			quotes[0]++;
		else if (quotes[0] % 2 == 0 && line[i[1]] == '\"')
			quotes[1]++;
		if (quotes[0] % 2 == 0 && line[i[1]] == '$'
			&& (ft_isalnum(line[i[1] + 1]) || line[i[1] + 1] == '?'))
			new = manage_var(data, new, line, i);
		i[1]++;
	}
	if (i[1] != i[0])
		new = ft_strjoin(new, &line[i[0]]);
	free(i);
	free(line);
	free(quotes);
	return (new);
}

char	*lexique_var(t_data *data, const char *cmd_line)
{
	char	*line;

	line = ft_strdup(cmd_line);
	line = replace_var_env(data, line);
	return (line);
}
