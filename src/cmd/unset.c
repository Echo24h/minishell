/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 00:31:56 by hvincent          #+#    #+#             */
/*   Updated: 2022/07/30 20:39:39 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// remove the lst[id] and return the new lst

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

static char **unset_id(char **lst, const int id)
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
		i++;
	}
	free(lst);
	return (new);
}

static char	*get_var(char *pre, char *var, char *suf)
{
	char *new;

	if (pre && suf)
	{
		new = ft_strjoin2(pre, var, 0, 0);
		new = ft_strjoin(new, suf);
	}
	else if (pre)
		new = ft_strjoin2(pre, var, 0, 0);
	else
		new = ft_strjoin2(var, suf, 0, 0);
	return (new);
}

//  check if the var is on list, format for list: separate start & end with '|' ex: "declare -x |="
static int	is_unset(const char *line, char *var, char *format)
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
	//printf("var=%s-\n", thisvar);
	if (ft_strncmp(thisvar, line, ft_strlen(thisvar)) == 0)
	{
		free(thisvar);
		return (1);
	}
	free(thisvar);
	return (0);
}

int	unset(t_cmd *cmd)
{
    int	i;

    i = -1;
	while(cmd->arg[1][++i])
		if (ft_isalnum(cmd->arg[1][i]) != 1)
			return printf("unset: \"%s\": not a valid identifier\n", cmd->arg[1]);
	i = -1;
	// export with "="
	while (cmd->data->export[++i])
	{
		if (is_unset(cmd->data->export[i], cmd->arg[1], "declare -x |="))
		{
			cmd->data->export = unset_id(cmd->data->export, i);
			break ;
		}
	}
	i = -1;
	// export without "="
	while (cmd->data->export[++i])
	{
		if (is_unset(cmd->data->export[i], cmd->arg[1], NULL))
		{
			cmd->data->export = unset_id(cmd->data->export, i);
			break ;
		}
	}
	i = -1;
	// envp
	while (cmd->data->envp[++i])
	{
		if (is_unset(cmd->data->envp[i], cmd->arg[1], "|="))
		{
			cmd->data->envp = unset_id(cmd->data->envp, i);
			break ;
		}
	}
	return (0);
}
