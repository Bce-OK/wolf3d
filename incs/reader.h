/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 17:17:18 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/06/24 17:17:21 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H

# ifdef WIN32
#  define _CRT_SECURE_NO_WARNINGS
#  include <stdio.h>
#  include <io.h>
#  define OPEN _open
#  define READ _read
#  define CLOSE _close
# else
#  include <unistd.h>
#  define OPEN open
#  define READ read
#  define CLOSE close
# endif
# include <fcntl.h>
# define ACTUAL_VERSION	1

int		read_buffer(int fd, size_t size, void *ret);
int		mapreader(int fd, t_map *map, int version);
#endif
