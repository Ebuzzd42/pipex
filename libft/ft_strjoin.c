/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egerin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:27:16 by egerin            #+#    #+#             */
/*   Updated: 2024/11/23 17:34:08 by egerin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1l;
	size_t	s2l;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	s1l = ft_strlen(s1);
	s2l = ft_strlen(s2);
	s3 = (char *)malloc(sizeof(char) * (s1l + s2l + 1));
	if (!s3)
		return (NULL);
	ft_memcpy(s3, s1, s1l);
	ft_memcpy(s3 + s1l, s2, s2l);
	s3[s1l + s2l] = '\0';
	return (s3);
}
