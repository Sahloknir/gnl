/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 22:42:55 by axbal             #+#    #+#             */
/*   Updated: 2018/01/16 13:18:37 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_got_the_line(char *stock)
{
	char	*line;
	int		i;

	i = 0;
	while (stock[i] != '\n' && stock[i] != '\0')
		i++;
	if (!(line = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	ft_memcpy(line, stock, i);
	line[i] = '\0';
	return (line);
}

char	*ft_dupncat(char *dst, char *src)
{
	char	*tmp;

	tmp = ft_strdup(dst);
	if (dst)
		free(dst);
	if (!(dst = malloc(sizeof(char) * ft_strlen(tmp) + ft_strlen(src) + 1)))
		return (NULL);
	dst = ft_strcpy(dst, tmp);
	dst = ft_strcat(dst, src);
	free(tmp);
	return (dst);
}

char	*ft_keep_stock(char *stock)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (stock[i] != '\n' && stock[i] != '\0')
		i++;
	if (stock[i] == '\0')
		ft_bzero(stock, ft_strlen(stock));
	while (stock[i + j] != '\0')
		j++;
	if (!(tmp = malloc(sizeof(char) * j + 1)))
		return (NULL);
	j = 0;
	while (stock[i + j] != '\0')
	{
		tmp[j] = stock[i + j];
		j++;
	}
	tmp[j] = '\0';
	free(stock);
	stock = ft_strdup(tmp);
	free(tmp);
	return (stock);
}

char	*ft_fill(char **line, char *stock)
{
	*line = ft_got_the_line(stock);
	stock = ft_keep_stock(stock);
	return (stock);
}

int		get_next_line(int fd, char **line)
{
	static char		*stock;
	char			buf[BUFF_SIZE];
	int				ret;

	if (fd < 1 || fd == 2)
		return (-1);
	if (ft_strstr(stock, "\n") != NULL)
	{
		*line = ft_got_the_line(stock);
		stock = ft_keep_stock(stock);
		return (1);
	}
	while (ft_strstr(stock, "\n") == NULL)
	{
		if ((ret = read(fd, buf, BUFF_SIZE)) == BUFF_SIZE)
		{
			buf[ret] = '\0';
			stock = ft_dupncat(stock, buf);
		}
		else if (ret == -1)
			return (-1);
		else
		{
			buf[ret] = '\0';
			break ;
		}
	}
	stock = ft_fill(line, stock);
	return (0);
}
