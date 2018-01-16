/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 12:24:58 by axbal             #+#    #+#             */
/*   Updated: 2018/01/15 17:34:10 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		find_line(char *buf, int ret)
{
	int		i;

	i = 0;
	if (buf == NULL)
		return (0);
	while (i < ret && buf[i])
	{
		if (buf[i] == '\n')
			return (1);
		if (buf[i] == '\0')
			return (2);
		i++;
	}
	return (0);
}

char	*fill_line(char *buf, char **line)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (buf[i] != '\0' && buf[i] != '\n')
		i++;
	if (*line != NULL)
		free(*line);
	if (!(*line = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	*line = ft_strncpy(*line, buf, i);
	tmp = ft_strdup(buf + i + 1);
	free(buf);
	buf = ft_strdup(tmp);
	free(tmp);
	return (buf);
}

char	*concat_buf(char *save, char *buf)
{
	char	*tmp;

	tmp = NULL;
	if (save != NULL)
	{
		tmp = ft_strdup(save);
		free(save);
		if (!(save = malloc(sizeof(char) * (ft_strlen(tmp) + ft_strlen(buf) + 1))))
			return (NULL);
		save = ft_strcpy(save, tmp);
		save = ft_strcat(save, buf);
		free(tmp);
	}
	else
	{
		if (!(save = malloc(sizeof(char) * (ft_strlen(buf) + 1))))
			return (NULL);
		save = ft_strcpy(save, buf);
	}
	return (save);
}

int		get_next_line(const int fd, char **line)
{
	int				stop;
	int				ret;
	char			buf[BUFF_SIZE + 1];
	static char		*save;

	stop = 0;
	if (fd < 1 || fd == 2)
		return (-1);
	while (stop == 0)
	{
		if ((ret = read(fd, buf, BUFF_SIZE)) > 0)
		{
			buf[ret] = '\0';
			stop = find_line(buf, ret);
			save = concat_buf(save, buf);
		}
		else
			stop = 2;
	}
	save = fill_line(save, line);
	if (stop == 2)
		return (0);
	return (1);
}
