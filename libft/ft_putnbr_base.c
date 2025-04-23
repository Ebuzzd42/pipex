/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egerin <egerin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:26:42 by egerin            #+#    #+#             */
/*   Updated: 2025/03/04 14:19:19 by egerin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(long n, int base)
{
	int		count;
	char	*symbols;

	symbols = "0123456789abcdef";
	if (n < 0)
	{
		write(1, "-", 1);
		return (ft_putnbr_base(-n, base) + 1);
	}
	else if (n < base)
		return (ft_putchar(symbols[n]));
	else
	{
		count = ft_putnbr_base(n / base, base);
		return (count + ft_putnbr_base(n % base, base));
	}
}

int	ft_putnbr_basemaj(long n, int base)
{
	int		count;
	char	*symbols;

	symbols = "0123456789ABCDEF";
	if (n < 0)
	{
		write(1, "-", 1);
		return (ft_putnbr_basemaj(-n, base) + 1);
	}
	else if (n < base)
		return (ft_putchar(symbols[n]));
	else
	{
		count = ft_putnbr_basemaj(n / base, base);
		return (count + ft_putnbr_basemaj(n % base, base));
	}
}

int	ft_putptr(size_t n, size_t base)
{
	int		count;
	char	*symbols;

	count = 0;
	symbols = "0123456789abcdef";
	if (n == 0)
	{
		ft_putstr("(nil)");
		return (5);
	}
	else if (n < base)
	{
		ft_putstr("0x");
		ft_putchar(symbols[n]);
		return (3);
	}
	else
	{
		count = ft_putptr(n / base, base);
		ft_putchar(symbols[n % base]);
		count += 1;
		return (count);
	}
}
