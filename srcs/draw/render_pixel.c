/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:23:22 by panger            #+#    #+#             */
/*   Updated: 2024/02/12 19:09:27 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	on_object(t_ray ray, t_scene *scene)
{
	int			i;
	t_sphere	*tmp;

	i = 0;
	// printf("vector %f %f %f\n", ray.vector.x,  ray.vector.y,  ray.vector.z);
	tmp = scene->sphere;
	while (tmp)
	{
		for (int i = 0; i < 5; i++)
		{
			// printf("getting distance with %f %f %f: value %f\n", ray.origin.x, (i * ray.vector.x), tmp->coords.x, (ray.origin.x + (i * ray.vector.x) - tmp->coords.x));
			// printf("getting distance with %f %f %f: value %f\n", ray.origin.y, (i * ray.vector.y), tmp->coords.y, (ray.origin.y + (i * ray.vector.y) - tmp->coords.y));
			// printf("getting distance with %f %f %f: value %f\n", ray.origin.z, (i * ray.vector.z), tmp->coords.z, (ray.origin.z + (i * ray.vector.z) - tmp->coords.z));
			// printf("distance %f\n", fabs(((ray.origin.x + (i * ray.vector.x) - tmp->coords.x)
				// + fabs(ray.origin.y + (i * ray.vector.y) - tmp->coords.y)
					// + fabs(ray.origin.z + (i * ray.vector.z) - tmp->coords.z))));
			// printf("diameter %f\n", tmp->diameter);
			if (fabs((ray.origin.x + (i * ray.vector.x) - tmp->coords.x)
				+ fabs(ray.origin.y + (i * ray.vector.y) - tmp->coords.y)
					+ fabs(ray.origin.z + (i * ray.vector.z) - tmp->coords.z))
					<= tmp->diameter)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
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

int	render_pixel(t_mlx *mlx, int x, int y)
{
	t_pair	pixel_ndc;
	t_pair	pixel_screen;
	t_ray	ray;

	pixel_ndc = assign_pair((x + 0.5) / WIDTH, (y + 0.5) / HEIGHT);
	pixel_screen = assign_pair(pixel_ndc.x * 2 - 1, pixel_ndc.y * 2 - 1);
	ray = ray_to_pixel(x, y, mlx->scene);
	if (on_object(ray, mlx->scene) == 1)
	{
		draw_pixel(mlx->img->buffer, calc_pixel(x, y, mlx->img), assign_color(0x53FF45), mlx->img->endian);
		printf("%d %d is in circle\n", x, y);
	}
	else
	{
		printf("%d %d is not in circle\n", x, y);
		draw_pixel(mlx->img->buffer, calc_pixel(x, y, mlx->img), assign_color(0x27010B), mlx->img->endian);
	}
	return (1);
}
