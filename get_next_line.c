/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 12:24:58 by axbal             #+#    #+#             */
/*   Updated: 2018/01/19 15:14:27 by axbal            ###   ########.fr       */
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
	char	*tmp;

	i = 0;
	if (!(buf))
	{
		*line = "";
		return (NULL);
	}
	while (buf[i] != '\0' && buf[i] != '\n')
		i++;
	buf[i] = '\0';
	if (*line)
		free(*line);
	*line = ft_strdup(buf);
	buf[i] = ' ';
	if (buf + i + 1)
	{
		tmp = ft_strdup(buf + i + 1);
		free(buf);
		buf = ft_strdup(tmp);
		free(tmp);
	}
	else
	{
		free(buf);
		return (NULL);
	}
	return (buf);
}

char	*concat_buf(char *save, char *buf)
{
	char	*tmp;
	int		size;

	tmp = NULL;
	if (save != NULL)
	{
		tmp = ft_strdup(save);
		free(save);
		size = ft_strlen(tmp) + ft_strlen(buf) + 1;
		if (!(save = malloc(sizeof(char) * size)))
			return (NULL);
		save = ft_strcpy(save, tmp);
		save = ft_strcat(save, buf);
		free(tmp);
	}
	else
	{
		size = ft_strlen(buf) + 1;
		save = ft_strdup(buf);
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
	if ((fd < 3 && fd != 0) || BUFF_SIZE <= 0)
		return (-1);
	if (save && find_line(save, ft_strlen(save)) == 1)
		stop = 1;
	while (stop == 0)
	{
		if ((ret = read(fd, buf, BUFF_SIZE)) > 0)
		{
			buf[ret] = '\0';
			stop = find_line(buf, ret);
			save = concat_buf(save, buf);
		}
		else if (ret == -1)
			return (-1);
		else
			stop = 3;
	}
	save = fill_line(save, line);
	if (stop == 3 && ft_strlen(*line) == 0)
		return (0);
	return (1);
}
