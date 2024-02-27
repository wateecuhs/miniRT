/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calculations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:53:08 by panger            #+#    #+#             */
/*   Updated: 2024/02/27 16:17:11 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_colors	apply_light(t_colors color, double rgb[3])
{
	t_colors	ret;

	ret.r = rgb[0] * color.r;
	ret.g = rgb[1] * color.g;
	ret.b = rgb[2] * color.b;
	return (ret);
}

int	intersect_spheres(t_ray ray, t_scene *scene)
{
	void	*tmp;
	double	ret;

	tmp = scene->sphere;
	while (tmp)
	{
		ret = intersect_sphere(ray, tmp);
		if (ret > 0)
			return (1);
		tmp = ((t_sphere *)tmp)->next;
	}
	return (0);
}

int	intersect_planes(t_ray ray, t_scene *scene)
{
	void	*tmp;
	double	ret;

	tmp = scene->plane;
	while (tmp)
	{
		ret = intersect_plane(ray, tmp);
		if (ret > 0)
			return (1);
		tmp = ((t_plane *)tmp)->next;
	}
	return (0);
}

int	intersect_cylinders(t_ray ray, t_scene *scene)
{
	void	*tmp;
	double	ret;

	tmp = scene->cylinder;
	while (tmp)
	{
		ret = intersect_cylinder(ray, tmp);
		if (ret > 0)
			return (1);
		tmp = ((t_cylinder *)tmp)->next;
	}
	return (0);
}

int	light_intersects(t_ray ray, t_scene *scene)
{
	if (intersect_spheres(ray, scene) || intersect_planes(ray, scene)
		|| intersect_cylinders(ray, scene))
		return (1);
	return (0);
}
