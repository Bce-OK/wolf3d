/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonts_cont.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpoudre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 16:16:04 by wpoudre           #+#    #+#             */
/*   Updated: 2020/06/25 16:16:07 by wpoudre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"

void	set_transparent(t_font *font)
{
	int	i;

	i = 0;
	while (i < font->full_h * font->full_w)
	{
		font->pixels[i] = (font->pixels[i] == font->transparent_color)
				? 0x00000000u
				: font->pixels[i];
		++i;
	}
}
