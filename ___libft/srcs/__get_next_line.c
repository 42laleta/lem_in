/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 00:41:51 by laleta            #+#    #+#             */
/*   Updated: 2019/08/06 00:42:47 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_read_data(int file_desc, char *read_data, char **storage)
{
	char		*str_tmp;
	int			ret;

	while ((ret = read(file_desc, read_data, BUFF_SIZE)) > 0)
	{
		read_data[ret] = '\0';
		if (*storage)
		{
			str_tmp = *storage;
			*storage = ft_strjoin(str_tmp, read_data);
			ft_strdel(&str_tmp);
		}
		else
			*storage = ft_strdup(read_data);
		if (ft_strchr(read_data, '\n'))
			break ;
	}
	ft_strdel(&read_data);
}

static int	ft_get_line(char **storage, char **line)
{
	char		*str_tmp;
	char		*str_tmp2;

	if (!*storage)
		return (0);
	if ((str_tmp = ft_strchr(*storage, '\n')) == NULL)
		return (0);
	*str_tmp = '\0';
	*line = ft_strdup(*storage);
	str_tmp2 = *storage;
	*storage = ft_strdup(str_tmp + 1);
	ft_strdel(&str_tmp2);
	return (1);
}

int			get_next_line(int const fd, char **line)
{
	static char *storage[MAX_FILE_DESC + 1];
	char		*read_data;
	int			ret;

	ret = 0;
	if (fd < 0 || fd > MAX_FILE_DESC || !line || read(fd, storage[fd], 0) < 0 ||
		!(read_data = ft_strnew(BUFF_SIZE)))
		return (-1);
	if (!ft_strchr(storage[fd], '\n'))
		ft_read_data(fd, read_data, &storage[fd]);
	if (ft_get_line(&storage[fd], line))
		return (1);
	else
	{
		if (!storage[fd] || storage[fd][0] == '\0')
			return (0);
	}
	*line = storage[fd];
	storage[fd] = NULL;
	return (1);
}
