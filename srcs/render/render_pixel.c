/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:23:22 by panger            #+#    #+#             */
/*   Updated: 2024/02/27 16:29:39 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	sphere_inter(t_scene *scene, t_colors *color,
			t_ray ray, double *closest)
{
	t_sphere	*tmp;
	double		ret;

	tmp = scene->sphere;
	while (tmp)
	{
		ret = intersect_sphere(ray, tmp);
		if (ret < *closest && ret > 0)
		{
			*closest = ret;
			*color = tmp->color;
			*color = light_calc_sph(create_ray(vec_add(ray.origin, ray.vector,
							*closest), ray.vector), scene, *color, tmp);
		}
		tmp = tmp->next;
	}
	return (*closest);
}

double	plane_inter(t_scene *scene, t_colors *color, t_ray ray, double *closest)
{
	t_plane		*tmp;
	double		ret;

	tmp = scene->plane;
	while (tmp)
	{
		ret = intersect_plane(ray, tmp);
		if (ret < *closest && ret > 0)
		{
			*closest = ret;
			*color = tmp->color;
			*color = light_calc_plane(create_ray(vec_add(ray.origin, ray.vector,
							*closest), ray.vector), scene, *color, tmp);
		}
		tmp = tmp->next;
	}
	return (*closest);
}

double	cylin_inter(t_scene *scene, t_colors *color, t_ray ray, double *closest)
{
	t_cylinder	*tmp;
	double		ret;

	tmp = scene->cylinder;
	while (tmp)
	{
		ret = intersect_cylinder(ray, tmp);
		if (ret < *closest && ret > 0)
		{
			*closest = ret;
			*color = tmp->color;
			*color = light_calc_cyl(create_ray(vec_add(ray.origin, ray.vector,
							*closest), ray.vector), scene, *color, tmp);
		}
		tmp = tmp->next;
	}
	return (*closest);
}

t_colors	get_all_intersections(t_ray ray, t_scene *scene)
{
	double		closest;
	t_colors	color;

	closest = INFINITY;
	color = assign_color(0x000000);
	sphere_inter(scene, &color, ray, &closest);
	plane_inter(scene, &color, ray, &closest);
	cylin_inter(scene, &color, ray, &closest);
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
