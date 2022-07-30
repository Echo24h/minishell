/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:24:45 by mbastard          #+#    #+#             */
/*   Updated: 2022/07/30 20:21:45 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_subdup(const char *s1, char c)
{
	char	*s2;

	s2 = (char *)ft_calloc(ft_sublen(s1, c) + 1, sizeof(char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s1, ft_sublen(s1, c) + 1);
	return (s2);
}
