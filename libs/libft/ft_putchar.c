/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 21:13:28 by hgreenfe          #+#    #+#             */
/*   Updated: 2018/11/26 22:04:39 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef OS_X
# include <unistd.h>
#else
# if __WIN32
#  define write _write
# else
#  include <sys/unistd.h>
//#  include <io.h>
# endif
#endif

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
