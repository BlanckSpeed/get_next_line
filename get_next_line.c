/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrigo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:25:16 by rodrigo           #+#    #+#             */
/*   Updated: 2024/07/26 18:51:06 by rlendine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*init_line(char *buffer, int *eol_loc)
{
	size_t	len;
	char	*line;

	len = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	len++;
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	ft_memcpy(line, buffer, len);
	line[len] = '\0';
	if (len > 0 && line[len - 1] == '\n')
		*eol_loc = len - 1;
	return (line);
}

size_t	locate_eol(char *line)
{
	size_t	i;

	i = 0;
	if (!line)
		return (-1);
	while (i < BUFFER_SIZE)
	{
		if (line[i] == '\n' || line[i] == '\0')
			return (i + 1);
		i++;
	}
	return (i);
}

char	*extract_line(char *line, char *buffer, int *eol_loc, int fd)
{
	char	temp_buffer[BUFFER_SIZE + 1];
	ssize_t	read_check;
	size_t	line_size;

	while (*eol_loc == -1)
	{
		gnl_bzero(temp_buffer, (BUFFER_SIZE + 1));
		read_check = read(fd, temp_buffer, BUFFER_SIZE);
		if (read_check == -1)
		{
			free(line);
			gnl_bzero(buffer, (BUFFER_SIZE + 1));
			return (NULL);
		}
		line_size = locate_eol(temp_buffer);
		ft_strlcpy_gnl(buffer, &temp_buffer[line_size], (BUFFER_SIZE + 1));
		temp_buffer[line_size] = '\0';
		line = ft_strjoin_gnl(line, temp_buffer, eol_loc);
		if (read_check == 0)
		{
			gnl_bzero(buffer, BUFFER_SIZE + 1);
			break ;
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			eol_loc;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	eol_loc = -1;
	line = init_line(buffer, &eol_loc);
	if (!line)
		return (NULL);
	ft_strlcpy_gnl(buffer, &buffer[eol_loc + 1], BUFFER_SIZE + 1);
	line = extract_line(line, buffer, &eol_loc, fd);
	if (!line || line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
/*
int	main(void)
{
	int		fd;
	int		cont;
	char	*str;
	char	*path;

	cont = 0;
	path = "/home/rlendine/42/get_next_line42/miFichero.txt";
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file");
		return (1);
	}
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		cont++;
		printf("[%d]:%s\n", cont, str);
		free(str);
		str = NULL;
	}
	close(fd);
	return (0);
}*/
