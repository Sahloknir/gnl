/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 17:05:44 by axbal             #+#    #+#             */
/*   Updated: 2018/03/08 17:35:24 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>
#include <fcntl.h>

int		main(int argc, char **argv)
{
	int		fd;
	int		ret;
	char	*line;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while ((ret = get_next_line(fd, &line)) > 0)
			printf("ret = %i ; line : %s\n", ret, line);
		printf("ret = %i ; line : %s\n", ret, line);
	}
	return (0);
}
