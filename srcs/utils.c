/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 18:27:30 by hgreenfe          #+#    #+#             */
/*   Updated: 2020/06/11 18:42:41 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"

unsigned int	get_color_by_len(unsigned char max_bright,
	numeric length, numeric max_length)
{
	unsigned int	bright;
	unsigned int	color;

	if (length < max_length)
		bright = (unsigned char)
			(max_bright / max_length * (max_length - length));
	else
		bright = 0;
	color = bright | (bright << 8u) | (bright << 16u) | (bright << 24u);
	return (color);
}