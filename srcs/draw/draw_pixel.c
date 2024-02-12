/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:07:32 by panger            #+#    #+#             */
/*   Updated: 2024/02/12 15:18:46 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	draw_pixel(char *buffer, int pixel, t_colors color, int endian)
{
	if (endian == 1)
	{
		buffer[pixel + 0] = color.a;
		buffer[pixel + 1] = color.r;
		buffer[pixel + 2] = color.g;
		buffer[pixel + 3] = color.b;
	}
	else if (endian == 0)
	{
		buffer[pixel + 0] = color.b;
		buffer[pixel + 1] = color.g;
		buffer[pixel + 2] = color.r;
		buffer[pixel + 3] = color.a;
	}
}

int	calc_pixel(int x, int y, t_img *img)
{
	int	pixel;

	pixel = (y * img->line_bytes) + (x * (img->pixel_bits / 8));
	return (pixel);
}
