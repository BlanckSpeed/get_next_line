/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrigo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:25:36 by rodrigo           #+#    #+#             */
/*   Updated: 2024/07/26 18:47:49 by rlendine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

# if BUFFER_SIZE > 125000 || BUFFER_SIZE < 1
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*extract_line(char *line, char *stash, int *eol_loc, int fd);
char	*init_line(char *stash, int *eol_loc);
size_t	locate_eol(char *line);

size_t	ft_strlen(const char *s);
void	gnl_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strjoin_gnl(char *s1, char *s2, int *eol_loc);
void	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize);
#endif
