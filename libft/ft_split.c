/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egerin <egerin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:39:01 by egerin            #+#    #+#             */
/*   Updated: 2024/11/22 15:46:51 by egerin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordlen(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

static char	**memfree(char **fr, int i)
{
	while (i >= 0)
	{
		free(fr[i]);
		i--;
	}
	free(fr);
	return (NULL);
}

static int	count_words(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] != c && str[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		wordlen;

	tab = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!tab || !s)
		return (NULL);
	i = 0;
	while (*s)
	{
		wordlen = 0;
		while (*s == c && *s)
			s++;
		wordlen = ft_wordlen(s, c);
		if (wordlen)
		{
			tab[i] = ft_substr(s, 0, wordlen);
			if (!tab[i])
				return (memfree(tab, i));
			i++;
		}
		s += wordlen;
	}
	tab[i] = 0;
	return (tab);
}
