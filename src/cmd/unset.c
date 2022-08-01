/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 21:13:24 by gborne            #+#    #+#             */
/*   Updated: 2022/08/01 20:11:10 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// remove the lst[id] and return the new lst
static char	**unset_id(char **lst, const int id)
{
	int		i;
	int		j;
	char	**new;

	new = (char **)ft_calloc((ft_tablen(lst)), sizeof(char *));
	i = 0;
	j = 0;
	while (lst[i])
	{
		if (i != id)
			new[j++] = lst[i];
		else
			free(lst[i]);
		i++;
	}
	free(lst);
	return (new);
}

static char	*get_var(char *pre, char *var, char *suf)
{
	char	*new;

	if (pre && suf)
	{
		new = ft_strjoin2(pre, var, 0, 0);
		new = ft_strjoin(new, suf);
	}
	else if (pre)
		new = ft_strjoin2(pre, var, 0, 0);
	else
		new = ft_strjoin2(var, suf, 0, 0);
	free(var);
	return (new);
}

// check if the var is on list, format for list: separate start & end
// with '|' ex: "declare -x |="
static int	is_unset(const char *line, const char *var, const char *format)
{
	char	**form;
	char	*thisvar;

	form = NULL;
	thisvar = ft_strdup(var);
	if (format == NULL)
		thisvar = get_var("declare -x ", thisvar, NULL);
	else
	{
		form = ft_split(format, '|');
		if (ft_tablen(form) == 1)
			thisvar = get_var(NULL, thisvar, form[0]);
		else if (ft_tablen(form) == 2)
			thisvar = get_var(form[0], thisvar, form[1]);
		free_tab(form);
	}
	if (ft_strncmp(thisvar, line, ft_strlen(thisvar)) == 0)
	{
		free(thisvar);
		return (1);
	}
	free(thisvar);
	return (0);
}

static char	**unset_form(char **lst, const char *arg, const char *format)
{
	int	i;

	i = -1;
	while (lst[++i])
	{
		if (is_unset(lst[i], arg, format))
		{
			lst = unset_id(lst, i);
			break ;
		}
	}
	return (lst);
}

int	unset(t_cmd *cmd)
{
	int	i;
	int	i_arg;

	i = -1;
	i_arg = 0;
	while (cmd->arg && cmd->arg[++i_arg])
	{
		while (cmd->arg[i_arg][++i])
			if (ft_isalnum(cmd->arg[i_arg][i]) != 1)
				return (printf("unset: \"%s\": not a valid identifier\n",
						cmd->arg[i_arg]));
		cmd->data->export = unset_form(cmd->data->export, cmd->arg[i_arg],
				"declare -x |=");
		cmd->data->export = unset_form(cmd->data->export, cmd->arg[i_arg], NULL);
		cmd->data->envp = unset_form(cmd->data->envp, cmd->arg[i_arg], "|=");
	}
	return (0);
}
