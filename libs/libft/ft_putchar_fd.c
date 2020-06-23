/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 21:13:28 by hgreenfe          #+#    #+#             */
/*   Updated: 2018/11/21 21:40:06 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __APPLE__
# include <unistd.h>
#else
# if WIN_32
#  define write _write
#  include <io.h>
# else
#  include <sys/unistd.h>
# endif
#endif

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
