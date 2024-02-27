/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcindrak <dcindrak@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:53:43 by dcindrak          #+#    #+#             */
/*   Updated: 2024/02/27 13:53:48 by dcindrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

void	add_coeficient(double (*rgb)[3], double coef, t_colors color)
{
	(*rgb)[0] += coef * color.r / 255;
	(*rgb)[1] += coef * color.g / 255;
	(*rgb)[2] += coef * color.b / 255;
}
