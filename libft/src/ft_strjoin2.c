/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbastard <mbastard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:34:28 by mbastard          #+#    #+#             */
/*   Updated: 2022/06/12 19:11:53 by mbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strjoin2(char *s1, char *s2, int clean_s1, int clean_s2)
{
	unsigned long	i;
	unsigned long	j;
	unsigned long	s1_len;
	unsigned long	s2_len;
	char			*dst;

	i = -1;
	j = -1;
	s1_len = ft_sublen(s1, 0);
	s2_len = ft_sublen(s2, 0);
	dst = (char *)ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (dst == NULL || (!s1_len && !s2_len))
		return (NULL);
	if (s1_len)
		while (s1[++i])
			dst[i] = s1[i];
	if (s2_len)
		while (s2[++j])
			dst[s1_len + j] = s2[j];
	dst[s1_len + s2_len] = 0;
	if (clean_s1)
		free(s1);
	if (clean_s2)
		free(s2);
	return (dst);
}