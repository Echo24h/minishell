/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 00:31:56 by hvincent          #+#    #+#             */
/*   Updated: 2022/07/30 20:42:25 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_if_equal(const char *s)
{
	int	i;

	i = -1;
	if (*s)
	{
		while (s[++i])
		{
			if (s[i] == '=')
				return (1);
			else if (s[i] == '$')
				return (2);
		}
	}
	return (0);
}

int	arg_is_diff(const char *cpy, const char *arg)
{
	int	i;

	i = 0;
	while (cpy[i])
	{
		if (arg[i] == '\0' && cpy[i] != '=')
			return (1);
		if (cpy[i] == '=')
			if (arg[i] == '=' || arg[i] == '\0')
				return (0);
		if (cpy[i] != '=' && arg[i] == '=')
			return (1);
		if (cpy[i] != arg[i])
			return (1);
		i++;
	}
	if (arg[i] == '=')
		return (2);
	else if (arg[i] == '\0')
		return (0);
	return (1);
}
