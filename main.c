/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 12:17:30 by axbal             #+#    #+#             */
/*   Updated: 2018/01/15 17:20:42 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int		main(int argc, char **argv)
{
	int		fd;
	int		retour;
	char	*line;

	line = NULL;
	if (argc == 1)
		return (0);
	fd = open (argv[1], O_RDONLY);
	while ((retour = get_next_line(fd, &line)) == 1)
	{
		ft_putnbr(retour);
		ft_putstr(line);
		ft_putchar('\n');
	}
	return (0);
}
