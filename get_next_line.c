/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:04:49 by mbartos           #+#    #+#             */
/*   Updated: 2023/11/02 14:59:53 by mbartos          ###   ########.fr       */
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

char *get_next_line(int fd)
{
	char		*buffer;
	char		*temp;
	static char	*new_buffer;
	int			n;
	int			i;
	int			a;

	new_buffer = (char *) ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	n = read(fd, new_buffer, BUFFER_SIZE);
	new_buffer[n] = 0;
	i = 0;
	a = 1;
	while (a == 1)
	{
		while (new_buffer[i])
		{
			if (new_buffer[i] == '\n' || new_buffer[i] == 0)
				break;
			else
				i++;
		}
		if (n == 0)
			return (NULL);
		else if(n == i)
		{
			temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
			n += read(fd, temp, BUFFER_SIZE);
			buffer = new_buffer;
			new_buffer = ft_strjoin(buffer, temp);
			free(buffer);
			free(temp);
			a = 1;
		}
		else
			a = 0;
	}
	if (new_buffer[i] == 0)
		return (NULL);
	while (i < n)
	{
		new_buffer[i] = 0;
		i++;
	}
	return (new_buffer);
}
