/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 21:43:50 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/03/12 21:09:35 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#define VERSION 0

int		read_buffer(int fd, size_t size, void *ret)
{
	size_t	read_data_size;

	if (!ret)
		return (-1);
	read_data_size = read(fd, ret, size);
	return (read_data_size != size);
}

int		read_map_size(int fd, t_map *map)
{
	if (read_buffer(fd, sizeof(char), &(map->size_x)) != NO_ERR ||
		read_buffer(fd, sizeof(char), &(map->size_y)) != NO_ERR)
		return (SIZE_ERR);
	if (map->size_x * map->size_y <= 0)
	{
		ft_putendl_fd("ERROR!\tmap size is 0 or negative!", FD_ERR);
		return (SIZE_ERR);
	}
	map->array = ft_memalloc(sizeof(int) * map->size_x * map->size_y);
	if (!(map->array))
	{
		ft_putendl_fd("ERROR!\tmap memory is not allocated!", FD_ERR);
		return (MEM_ERR);
	}
	return (NO_ERR);
}

int		mapreader0(int fd, t_map *map)
{
	int		i;
	int		int_buf;
	int		err;

	if ((err = read_map_size(fd, map)) != NO_ERR)
		return (err);
	i = 0;
	int_buf = 0;
	while (read_buffer(fd, sizeof(char), &int_buf) == NO_ERR)
	{
		if (i > map->size_x * map->size_y)
		{
			ft_putendl_fd(
				"WARNING!\tmap size bigger than map size has been set."
				" File reading was interrupted.", FD_ERR);
			break ;
		}
		map->array[i] = int_buf;
		++i;
	}
	if (i < map->size_x * map->size_y)
		ft_putendl_fd(
			"WARNING!\tmap size less than map size has been set."
			" Map tail was zero-filled.", FD_ERR);
	return (NO_ERR);
}

int		mapreader(int fd, t_map *map, int version)
{
	if (version == 0)
		return (mapreader0(fd, map));
	return (VERSION_ERR);
}

t_map	*load_map_from_file(char const *filename)
{
	t_map	*map;
	int		fd;
	int		int_buf;

	fd = open(filename, O_RDONLY);
	if (!fd)
		return (NULL);
	map = ft_memalloc(sizeof(t_map));
	int_buf = 0;
	if (read_buffer(fd, sizeof(char), &int_buf) == NO_ERR)
	{
		if (mapreader(fd, map, int_buf) != NO_ERR)
		{
			ft_putendl_fd("ERROR!\tmap reading error!", FD_ERR);
			ft_memdel((void**)&map);
		}
	}
	close(fd);
	return (map);
}
