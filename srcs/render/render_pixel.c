/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcindrak <dcindrak@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:23:22 by panger            #+#    #+#             */
/*   Updated: 2024/02/27 11:40:39 by dcindrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_colors	add_colors(t_colors color1, t_colors color2, double coef)
{
	t_colors	ret;

	ret.r = color2.r + (color1.r * coef);
	ret.g = color2.g + (color1.g * coef);
	ret.b = color2.b + (color1.b * coef);
	return (ret);
}

t_colors	get_all_intersections(t_ray ray, t_scene *scene)
{
	void		*tmp;
	double		closest;
	double		ret;
	t_colors	color;

	tmp = scene->sphere;
	closest = INFINITY;
	color = assign_color(0x000000);
	while (tmp)
	{
		ret = intersect_sphere(ray, tmp);
		if (ret < closest && ret > 0)
		{
			closest = ret;
			color = ((t_sphere *)tmp)->color;
			color = light_calc_sph(create_ray(vec_add(ray.origin, ray.vector, closest), ray.vector), scene, color, tmp);
		}
		tmp = ((t_sphere *)tmp)->next;
	}
	tmp = scene->plane;
	while (tmp)
	{
		ret = intersect_plane(ray, tmp);
		if (ret < closest && ret > 0)
		{
			closest = ret;
			color = ((t_plane *)tmp)->color;
			color = light_calc_plane(create_ray(vec_add(ray.origin, ray.vector, closest), ray.vector), scene, color, tmp);
		}
		tmp = ((t_plane *)tmp)->next;
	}
	tmp = scene->cylinder;
	while (tmp)
	{
		ret = intersect_cylinder(ray, tmp);
		if (ret < closest && ret > 0)
		{
			closest = ret;
			color = ((t_cylinder *)tmp)->color;
			color = light_calc_cyl(create_ray(vec_add(ray.origin, ray.vector, closest), ray.vector), scene, color, tmp);
		}
		tmp = ((t_cylinder *)tmp)->next;
	}
	return (color);
}

int	render_pixel(t_mlx *mlx, int x, int y)
{
	t_ray		ray;
	t_colors	colors;

	ray = ray_to_pixel(x, y, mlx->scene);
	colors = get_all_intersections(ray, mlx->scene);
	draw_pixel(mlx->img->buffer, calc_pixel(x, y, mlx->img),
		colors, mlx->img->endian);
	return (1);
}
