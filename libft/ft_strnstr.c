/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egerin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:00:51 by egerin            #+#    #+#             */
/*   Updated: 2024/11/23 17:30:46 by egerin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	len_s2;

	i = 0;
	len_s2 = ft_strlen(s2);
	if (len_s2 == 0)
		return ((char *)s1);
	while (i < n && s1[i])
	{
		j = 0;
		while (s2[j] == s1[i + j] && i + j < n && s1[i + j])
			j++;
		if (j == len_s2)
			return ((char *)(s1 + i));
		i++;
	}
	return (NULL);
}
