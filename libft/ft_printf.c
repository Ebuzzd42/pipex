/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egerin <egerin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:39:40 by egerin            #+#    #+#             */
/*   Updated: 2025/04/29 22:14:58 by egerin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format(char c, va_list ap)
{
	if (c == 'c')
		return (ft_putchar(va_arg(ap, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(ap, char *)));
	else if (c == 'd')
		return (ft_putnbr_base(va_arg(ap, int), 10));
	else if (c == 'i')
		return (ft_putnbr_base(va_arg(ap, int), 10));
	else if (c == 'u')
		return (ft_putnbr_base(va_arg(ap, unsigned int), 10));
	else if (c == 'x')
		return (ft_putnbr_base(va_arg(ap, unsigned int), 16));
	else if (c == 'X')
		return (ft_putnbr_basemaj(va_arg(ap, unsigned int), 16));
	else if (c == '%')
		return (ft_putchar('%'));
	else if (c == 'p')
		return (ft_putptr(va_arg(ap, unsigned long long), 16));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	size_t	compteur;
	size_t	i;

	va_start(ap, s);
	if (!s)
		return (-1);
	compteur = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			compteur += ft_format(s[i + 1], ap);
			i++;
		}
		else
			compteur += ft_putchar(s[i]);
		i++;
	}
	va_end(ap);
	return (compteur);
}
