/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calculations2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcindrak <dcindrak@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:29:14 by dcindrak          #+#    #+#             */
/*   Updated: 2024/02/27 12:43:42 by dcindrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_colors	light_calc_sph(t_ray ray, t_scene *sc, t_colors cl, t_sphere *sph)
{
	t_vectors	light;
	double		coef;
	t_vectors	normal;
	double		rgb[3];

	normal = vec_substract(sph->coords, ray.origin);
	if (vec_cos(ray.vector, normal) > 0)
		normal = vec_multiply(normal, -1);
	light = vec_substract(sc->light->coords, ray.origin);
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	add_coeficient(&rgb, sc->ambient_light->ratio, sc->ambient_light->color);
	coef = vec_dot(normal, light);
	if (coef > 0 && light_intersects(create_ray(ray.origin, light), sc) == 0)
	{
		coef = vec_cos(normal, light) * sc->light->brightness;
		add_coeficient(&rgb, coef, sc->light->color);
	}
	cl = apply_light(cl, rgb);
	return (cl);
}

t_colors	light_calc_cyl(t_ray ray, t_scene *sc, t_colors cl, t_cylinder *cy)
{
	t_vectors	light;
	double		coef;
	t_vectors	normal;
	double		rgb[3];

	normal = cy->normal;
	light = vec_substract(sc->light->coords, ray.origin);
	coef = vec_dot(normal, light);
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	add_coeficient(&rgb, sc->ambient_light->ratio, sc->ambient_light->color);
	if (coef > 0 && light_intersects(create_ray(ray.origin, light), sc) == 0)
	{
		coef = vec_cos(normal, light) * sc->light->brightness;
		add_coeficient(&rgb, coef, sc->light->color);
	}
	cl = apply_light(cl, rgb);
	return (cl);
}

t_colors	light_calc_plane(t_ray ray, t_scene *sc, t_colors cl, t_plane *pl)
{
	t_vectors	light;
	double		coef;
	t_vectors	normal;
	double		rgb[3];

	normal = pl->vectors;
	if (vec_cos(ray.vector, pl->vectors) > 0)
		normal = vec_multiply(pl->vectors, -1);
	light = vec_substract(sc->light->coords, ray.origin);
	coef = vec_dot(normal, light);
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	add_coeficient(&rgb, sc->ambient_light->ratio, sc->ambient_light->color);
	if (coef > 0 && light_intersects(create_ray(ray.origin, light), sc) == 0)
	{
		coef = vec_cos(normal, light) * sc->light->brightness;
		add_coeficient(&rgb, coef, sc->light->color);
	}
	cl = apply_light(cl, rgb);
	return (cl);
}
