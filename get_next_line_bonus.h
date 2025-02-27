/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marshaky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 00:07:48 by marshaky          #+#    #+#             */
/*   Updated: 2025/02/25 17:30:15 by marshaky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
// # include <limits.h>

char	*get_next_line(int fd);
char	*ft_strcpy_joined(char *res, char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
int		ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*ft_read_until_newline(int fd, char *buffer);
char	*ft_save_remainder(char *buffer);
char	*ft_extract_line(char *buffer);

#endif