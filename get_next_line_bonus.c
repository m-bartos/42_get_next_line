/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:04:49 by mbartos           #+#    #+#             */
/*   Updated: 2023/11/04 20:00:22 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *) s;
	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char) c)
			return (&str[i]);
		i++;
	}
	if ((unsigned char) c == '\0')
		return (&str[i]);
	return (NULL);
}

char	*file_read(char	*buffer, int fd, int *size)
{
	char	*buffer_add;
	char	*old_buffer;

	buffer_add = (char *) ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	*size = read(fd, buffer_add, BUFFER_SIZE);
	old_buffer = buffer;
	buffer = ft_strjoin(old_buffer, buffer_add);
	free(buffer_add);
	free(old_buffer);
	return (buffer);
}

char	*read_line(char	*buffer)
{
	int		i;
	int		len;
	char	*line;

	len = 0;
	while (buffer[len] != '\n' && buffer[len] != '\0' )
		len++;
	if (buffer[len] == '\n')
		len++;
	line = (char *) ft_calloc(len + 1, sizeof(char));
	i = 0;
	while (i < len)
	{
		line[i] = buffer[i];
		i++;
	}
	return (line);
}

char	*remove_line(char	*buffer)
{
	char	*temp;

	temp = ft_strchr(buffer, '\n');
	if (temp != NULL)
	{
		temp = ft_strjoin(temp + 1, "");
		free(buffer);
		return (temp);
	}
	else
	{
		free(buffer);
		return (NULL);
	}
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			size;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (NULL);
	size = BUFFER_SIZE;
	if (buffer == 0)
		buffer = (char *) ft_calloc(1, sizeof(char));
	while ((!ft_strchr(buffer, '\n')) && size == BUFFER_SIZE)
		buffer = file_read(buffer, fd, &size);
	line = read_line(buffer);
	buffer = remove_line(buffer);
	if (*line == '\0')
	{
		free (line);
		return (NULL);
	}
	return (line);
}
