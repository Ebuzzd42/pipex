/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egerin <egerin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:45:30 by egerin            #+#    #+#             */
/*   Updated: 2025/04/02 13:30:33 by egerin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ssize_t read (int fd, void *buf, size_t count);

#include "libft.h"

char	*ft_next_line(char *buffer)
{
	int		i;
	int		j;
	char	*next_line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	next_line = (char *)malloc((ft_strlen_gnl(buffer) - i + 1) * sizeof(char));
	if (!next_line)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		next_line[j++] = buffer[i++];
	next_line[j] = '\0';
	free(buffer);
	return (next_line);
}

char	*ft_first_line(char *buffer)
{
	int		i;
	char	*first_line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	first_line = (char *)malloc((i + 2) * sizeof(char));
	if (!first_line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		first_line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
	{
		first_line[i] = buffer[i];
		i++;
	}
	first_line[i] = '\0';
	return (first_line);
}

char	*ft_read(int fd, char *str)
{
	int		bytes;
	char	*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(str);
			free(buffer);
			return (NULL);
		}
		buffer[bytes] = 0;
		str = ft_strjoin_gnl(str, buffer);
		if (ft_strchr_gnl(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*first_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read(fd, buffer);
	if (!buffer)
		return (NULL);
	first_line = ft_first_line(buffer);
	buffer = ft_next_line(buffer);
	return (first_line);
}

/*#include <stdio.h>

int	main(void)
{
	int	fd;

	fd = open("test.txt", O_RDONLY);
	printf("Lecture du fichier =\n[%s]\n", get_next_line(fd));
	close(fd);
	return (0);
}*/
