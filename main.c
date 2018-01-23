/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 12:17:30 by axbal             #+#    #+#             */
/*   Updated: 2018/01/23 15:40:45 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static void simple_string2(void)
{
	char 	*line;
	int		out;
	int		p[2];
	int		fd;
	int		ret;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "mnopqrstuvwxyzab", 16);
	close(p[1]);
	dup2(out, fd);
	ret = get_next_line(p[0], &line);
	printf("%s", line);
}

void	simple_string(void)
{
	char 	*line;
	int		out;
	int		p[2];
	int		fd;
	int		ret;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "abcd\n", 5);
	write(fd, "efgh\n", 5);
	close(p[1]);
	dup2(out, fd);
	ret = get_next_line(p[0], &line);
	printf("%d ", ret);
	printf("%s\n", line);
	ret = get_next_line(p[0], &line);
	printf("%d ", ret);
	printf("%s\n", line);
	ret = get_next_line(p[0], &line);
	printf("%d\n", ret);
}

int		main(int argc, char **argv)
{
	int		fd;
	int		retour;
	char	*line;

	line = NULL;
	if (argc == 1)
		return (0);
//	simple_string();
//	simple_string2();
	fd = open (argv[1], O_RDONLY);
//	while ((retour = get_next_line(fd, &line)) == 1)
//	{
		retour = get_next_line(fd, &line);
		ft_putnbr(retour);
		ft_putstr(line);
		ft_putchar('\n');
		retour = get_next_line(fd, &line);
		ft_putnbr(retour);
		ft_putstr(line);
		ft_putchar('\n');
		retour = get_next_line(fd, &line);
		ft_putnbr(retour);
		ft_putstr(line);
		ft_putchar('\n');
		retour = get_next_line(fd, &line);
		ft_putnbr(retour);
		ft_putstr(line);
		ft_putchar('\n');
//	}
	return (0);
}
