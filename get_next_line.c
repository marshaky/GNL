/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marshaky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 00:06:10 by marshaky          #+#    #+#             */
/*   Updated: 2025/02/23 02:48:58 by marshaky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char *str)
{
	size_t	i;
	char	*line;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	ft_strncpy(line, str, i + 1);
	line[i + 1] = '\0';
	return (line);
}

char	*update_remainder(char *str)
{
	char	*new_remainder;
	char	*newline_pos;

	newline_pos = ft_strchr(str, '\n');
	if (!newline_pos)
	{
		free(str);
		return (NULL);
	}
	new_remainder = ft_strdup(newline_pos + 1);
	free(str);
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder = NULL;
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remainder)
		remainder = ft_strdup("");
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		remainder = ft_strjoin(remainder, buffer);
		if (ft_strchr(remainder, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0 || (bytes_read == 0 && !remainder))
		return (NULL);
	line = extract_line(remainder);
	remainder = update_remainder(remainder);
	return (line);
}
