/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:52:45 by panger            #+#    #+#             */
/*   Updated: 2024/02/27 16:31:28 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_colors	assign_color(__uint32_t color)
{
	t_colors	ret;

	ret.a = color >> 24;
	ret.r = color >> 16;
	ret.g = color >> 8;
	ret.b = color >> 0;
	return (ret);
}

void	add_coeficient(double (*rgb)[3], double coef, t_colors color)
{
	(*rgb)[0] += coef * color.r / 255;
	(*rgb)[1] += coef * color.g / 255;
	(*rgb)[2] += coef * color.b / 255;
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
