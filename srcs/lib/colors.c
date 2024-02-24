/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:52:45 by panger            #+#    #+#             */
/*   Updated: 2024/02/24 13:51:12 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_colors	multiply_colors(t_colors color, t_colors new, double ratio)
{
	t_colors	ret;

	ret.r = color.r + ((new.r - color.r) * ratio);
	ret.g = color.g + ((new.g - color.g) * ratio);
	ret.b = color.b + ((new.b - color.b) * ratio);
	ret.a = color.a + ((new.a - color.a) * ratio);
	return (ret);
}

t_colors	add_ambient(t_colors color, t_ambient *ambient)
{
	t_colors	ret;

	ret.r = color.r + ((ambient->color.r - color.r) * ambient->ratio);
	ret.g = color.g + ((ambient->color.g - color.g) * ambient->ratio);
	ret.b = color.b + ((ambient->color.b - color.b) * ambient->ratio);
	ret.a = color.a + ((ambient->color.a - color.a) * ambient->ratio);
	return (ret);
}

t_colors	create_color(__uint8_t a, __uint8_t r, __uint8_t g, __uint8_t b)
{
	t_colors	ret;

	ret.a = a;
	ret.r = r;
	ret.g = g;
	ret.b = b;
	return (ret);
}

int	color_to_int(t_colors color)
{
	int	ret;

	ret = color.a << 24 | color.r << 16 | color.g << 8 | color.b;
	return (ret);
}

t_colors	assign_color(__uint32_t color)
{
	t_colors	ret;

	ret.a = color >> 24;
	ret.r = color >> 16;
	ret.g = color >> 8;
	ret.b = color >> 0;
	return (ret);
}
