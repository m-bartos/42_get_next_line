/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:08:56 by mbartos           #+#    #+#             */
/*   Updated: 2023/11/14 11:14:32 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"

// cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 *.c ./tests/main.c && ./a.out

#include <stdio.h>

void	print_string_fd(int fd, char *line)
{
	line = get_next_line(fd);
	printf("Line: |%s|\n", line);
	free(line);
}

int	main(void)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open("read_error.txt", O_RDONLY);
	if (fd == -1)
		write(2, "Problem opening file.", 21);
	print_string_fd(fd, line);
	print_string_fd(fd, line);
	print_string_fd(fd, line);
	close(fd);
	fd = open("read_error.txt", O_RDONLY);
	if (fd == -1)
		write(2, "Problem opening file.", 21);
	print_string_fd(fd, line);
	print_string_fd(fd, line);
	print_string_fd(fd, line);
	print_string_fd(fd, line);
	print_string_fd(fd, line);
	close(fd);
	return (0);
}
