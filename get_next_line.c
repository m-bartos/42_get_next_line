/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:04:49 by mbartos           #+#    #+#             */
/*   Updated: 2023/11/03 15:15:12 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*memory;
	unsigned char	*memory_first;
	unsigned int	max_int;
	unsigned int	i;

	max_int = 2147483647;
	if (count > max_int && size > max_int)
		return (NULL);
	memory = (unsigned char *) malloc(count * size);
	if (memory == NULL)
		return (NULL);
	memory_first = memory;
	i = 0;
	while (i < (count * size))
	{
		*memory++ = 0;
		i++;
	}
	return ((void *) memory_first);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*str_first;
	int		str_len;

	str_len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *) malloc((str_len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str_first = str;
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (str_first);
}

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
	return (0);
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
	return(buffer);
}

char	*read_line(char	*buffer)
{
	int		i;
	int		len;
	char	*line;

	len = 0;
	while(buffer[len] != '\n' && buffer[len] != '\0' )
		len++;	
	line = (char *) ft_calloc(len + 2, sizeof(char));
	i = 0;
	while(i < len)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\n';
	return(line);
}

char	*remove_line(char	*buffer)
{
	char	*temp;

	temp = ft_strchr(buffer, '\n');
	temp = ft_strjoin(temp + 1, "");
	free(buffer);
	return(temp);
}

char *get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			size;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0,0) < 0)
		return (NULL);
	size = BUFFER_SIZE;
	if (buffer == 0)
		buffer = (char *) ft_calloc(1, sizeof(char));
	while ((!ft_strchr(buffer, '\n')) && size == BUFFER_SIZE)
		buffer = file_read(buffer, fd, &size);
	line = read_line(buffer);
	if (size == BUFFER_SIZE)
		buffer = remove_line(buffer);
	return (line);
}




/*
char *get_next_line(int fd)
{
	char		*old_buffer;
	char		*temp;
	static char	*buffer;
	int			size;
	int			n;
	int			i;
	int			a;

	n = 0;
	a = 1;
	i = 0;
	if (buffer != NULL)
	{
		temp = ft_strchr(buffer, '\n');
		if (*temp != 0)
		{
			line = ft_strjoin("", buffer);
			temp = ft_strjoin(temp + 1, "");
			free(buffer);
			buffer = temp;
		}
	}
	else
		buffer = (char *) ft_calloc(1, sizeof(char));
	if (buffer != NULL)
	{
		temp = ft_strchr(buffer, '\n');
	}
	while (a == 1)
	{
		temp = (char *) ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		size = read(fd, temp, BUFFER_SIZE);
		old_buffer = buffer;
		buffer = ft_strjoin(old_buffer, temp);
		free(temp);
		free(old_buffer);
		n += size;
		if (size < BUFFER_SIZE)
			break;
		while (buffer[i])
		{
			if (buffer[i] == '\n' || buffer[i] == 0)
				break;
			else
				i++;
		}
		if (n == size && size == 0)
		{
			return (buffer);
		}
		if(n != i)
			a = 0;
	}
	return (buffer);
}
*/


#include<stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		write(2, "Problem opening file.", 21);
	line = get_next_line(fd);
	printf("Line: |%s|\n", line);
	free(line);
	line = get_next_line(fd);
	printf("Line: |%s|\n", line);
	free(line);
	line = get_next_line(fd);
	printf("Line: |%s|\n", line);
	free(line);
	line = get_next_line(fd);
	printf("Line: |%s|\n", line);
	free(line);
	close(fd);
	return (0);
}
