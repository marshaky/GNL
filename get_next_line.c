/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marshaky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 00:06:10 by marshaky          #+#    #+#             */
/*   Updated: 2025/03/26 03:22:45 by marshaky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read_until_newline(int fd, char *buffer)
{
	int		byte_read;
	char	buff[BUFFER_SIZE + 1];

	*buff = 0;
	byte_read = 1;
	while (!ft_strchr(buff, '\n') && byte_read > 0)
	{
		byte_read = read(fd, buff, BUFFER_SIZE);
		if (byte_read < 0)
		{
			if (buffer)
			{
				free(buffer);
				buffer = NULL;
			}
			return (NULL);
		}
		buff[byte_read] = '\0';
		if (!buffer)
			buffer = ft_strdup(buff);
		else
			buffer = ft_strjoin(buffer, buff);
	}
	return (buffer);
}

static int	sep(char c, char a)
{
	if (c == a)
		return (1);
	return (0);
}

static char	*ft_extract_line(char *buffer)
{
	int		i;
	char	*str;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + (sep(buffer[i], '\n')) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		str[i] = buffer[i];
		i++;
	}
	if (sep(buffer[i], '\n'))
	{
		str[i++] = '\n';
		str[i] = '\0';
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_save_remainder(char *buffer)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		str[j++] = buffer[i++];
	str[j] = '\0';
	free(buffer);
	buffer = NULL;
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
	{
		if (buffer)
		{
			free(buffer);
			buffer = NULL;
		}
		return (NULL);
	}
	buffer = ft_read_until_newline(fd, buffer);
	if (!buffer)
	{
		buffer = NULL;
		return (NULL);
	}
	line = ft_extract_line(buffer);
	buffer = ft_save_remainder(buffer);
	if (!buffer)
		buffer = NULL;
	return (line);
}
/*
 #include <stdio.h>

 int	main()
 {
 	int	fd = open("test.txt", O_RDONLY);

 	printf("%s\n", get_next_line(fd));
 	printf("%s\n", get_next_line(fd));
 }*/
