/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:23:22 by panger            #+#    #+#             */
/*   Updated: 2024/02/20 17:29:19 by panger           ###   ########.fr       */
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

int	intersect(t_ray ray, t_scene *scene)
{
	t_sphere	*tmp;
	t_vectors	dist;
	double		a;
	double		b;
	double		c;
	double		delta;

	tmp = scene->sphere;
	while (tmp)
	{
		a = vec_dot(ray.vector, ray.vector);
		dist = substract(ray.origin, tmp->coords);
		b = 2 * vec_dot(ray.vector, dist);
		c = vec_dot(dist, dist) - (tmp->diameter * tmp->diameter);
		delta = ((b * b) - 4 * (a * c));
		if (delta >= 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	intersect_plane(t_ray ray, t_scene *scene)
{
	t_plane	*tmp;
	double		a;
	t_vectors	b;
	double		x;

	tmp = scene->plane;
	while (tmp)
	{
		a = vec_dot(tmp->vectors, ray.vector);
		if (a != 0)
		{
			x = (vec_dot(tmp->vectors, substract(tmp->coords, ray.origin))) / a;
			if (x > 0)
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	render_pixel(t_mlx *mlx, int x, int y)
{
	t_ray	ray;

	ray = ray_to_pixel(x, y, mlx->scene);
	if (intersect(ray, mlx->scene) == 1)
		draw_pixel(mlx->img->buffer, calc_pixel(x, y, mlx->img), assign_color(0xF3F9D2), mlx->img->endian);
	else if (intersect_plane(ray, mlx->scene) == 1)
		draw_pixel(mlx->img->buffer, calc_pixel(x, y, mlx->img), assign_color(0x53FF45), mlx->img->endian);
	else
		draw_pixel(mlx->img->buffer, calc_pixel(x, y, mlx->img), assign_color(0x27010B), mlx->img->endian);
	return (1);
}
