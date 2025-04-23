/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egerin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:23:54 by egerin            #+#    #+#             */
/*   Updated: 2024/11/18 11:56:02 by egerin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	x;
	void	*y;

	x = nmemb * size;
	y = malloc(x);
	if (y == NULL)
		return (NULL);
	ft_bzero(y, x);
	return (y);
}
