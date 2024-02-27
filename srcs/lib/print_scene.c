/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcindrak <dcindrak@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:38:47 by panger            #+#    #+#             */
/*   Updated: 2024/02/27 13:34:11 by dcindrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_objects(t_scene *scene)
{
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;

	sp = scene->sphere;
	while (sp)
	{
		print_sphere(sp);
		sp = sp->next;
	}
	pl = scene->plane;
	while (pl)
	{
		print_plane(pl);
		pl = pl->next;
	}
	cy = scene->cylinder;
	while (cy)
	{
		print_cylinder(cy);
		cy = cy->next;
	}
}

void	print_scene(t_scene *scene)
{
	if (scene->ambient_light)
		printf("Ambient light:\nColors: %.1hhu %.1hhu %.1hhu\nRatio: %.1f\n\n", \
		scene->ambient_light->color.r, scene->ambient_light->color.g, \
		scene->ambient_light->color.b, scene->ambient_light->ratio);
	print_light(scene->light);
	print_camera(scene->camera);
	print_objects(scene);
}

/*
void	print_scene(t_scene *scene)
{
	t_sphere	*tmp;
	t_plane		*tmp1;
	t_cylinder	*tmp2;
	if (scene->ambient_light)
		printf("Ambient light:\nColors: %.1hhu %.1hhu %.1hhu\nRatio: %.1f\n\n", scene->ambient_light->color.r, scene->ambient_light->color.g, scene->ambient_light->color.b, scene->ambient_light->ratio);
	if (scene->light)
		printf("Light:\nColors: %.1hhu %.1hhu %.1hhu\nBrightness: %.1f\nCoords: %.1f %.1f %.1f\n\n", scene->light->color.r, scene->light->color.g, scene->light->color.b, scene->light->brightness, scene->light->coords.x, scene->light->coords.y, scene->light->coords.z);
	if (scene->camera)
		printf("Camera:\nVectors: %.1f %.1f %.1f\nFov: %.1hhu\nCoords: %.1f %.1f %.1f\n\n", scene->camera->vectors.x, scene->camera->vectors.y, scene->camera->vectors.z,  scene->camera->fov, scene->camera->coords.x, scene->camera->coords.y, scene->camera->coords.z);
	tmp = scene->sphere;
	while (tmp)
	{
		printf("Sphere:\nColors: %.1hhu %.1hhu %.1hhu\nDiameter: %.1f\nCoords: %.1f %.1f %.1f\n\n", tmp->color.r, tmp->color.g, tmp->color.b,  tmp->diameter, tmp->coords.x, tmp->coords.y, tmp->coords.z);
		tmp = tmp->next;
	}
	tmp1 = scene->plane;
	while (tmp1)
	{
		printf("Plane:\nColors: %.1hhu %.1hhu %.1hhu\nVectors: %.1f %.1f %.1f\nCoords: %.1f %.1f %.1f\n\n", tmp1->color.r, tmp1->color.g, tmp1->color.b,  tmp1->vectors.x, tmp1->vectors.y, tmp1->vectors.z, tmp1->coords.x, tmp1->coords.y, tmp1->coords.z);
		tmp1 = tmp1->next;
	}
	tmp2 = scene->cylinder;
	while (tmp2)
	{
		printf("Cylinder:\nColors: %.1hhu %.1hhu %.1hhu\nVectors: %.1f %.1f %.1f\nCoords: %.1f %.1f %.1f\nDiameter: %.1f\nHeight: %.1f\n\n", tmp2->color.r, tmp2->color.g, tmp2->color.b,  tmp2->vectors.x, tmp2->vectors.y, tmp2->vectors.z, tmp2->coords.x, tmp2->coords.y, tmp2->coords.z, tmp2->diameter, tmp2->height);
		tmp2 = tmp2->next;
	}
}*/
