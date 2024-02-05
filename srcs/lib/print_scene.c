/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:38:47 by panger            #+#    #+#             */
/*   Updated: 2024/02/05 11:04:57 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_scene(t_scene *scene)
{
	if (scene->ambient_light)
		printf("Ambient light:\nColors: %.1hhu %.1hhu %.1hhu\nRatio: %.1f\n\n", scene->ambient_light->color.r, scene->ambient_light->color.g, scene->ambient_light->color.b, scene->ambient_light->ratio);
	if (scene->light)
		printf("Light:\nColors: %.1hhu %.1hhu %.1hhu\nBrightness: %.1f\nCoords: %.1f %.1f %.1f\n\n", scene->light->color.r, scene->light->color.g, scene->light->color.b, scene->light->brightness, scene->light->coords.x, scene->light->coords.y, scene->light->coords.z);
	if (scene->camera)
		printf("Camera:\nVectors: %.1f %.1f %.1f\nFov: %.1hhu\nCoords: %.1f %.1f %.1f\n\n", scene->camera->vectors.x, scene->camera->vectors.y, scene->camera->vectors.z,  scene->camera->fov, scene->camera->coords.x, scene->camera->coords.y, scene->camera->coords.z);
	if (scene->sphere)
		printf("Sphere:\nColors: %.1hhu %.1hhu %.1hhu\nDiameter: %.1f\nCoords: %.1f %.1f %.1f\n\n", scene->sphere->color.r, scene->sphere->color.g, scene->sphere->color.b,  scene->sphere->diameter, scene->sphere->coords.x, scene->sphere->coords.y, scene->sphere->coords.z);
	if (scene->plane)
		printf("Plane:\nColors: %.1hhu %.1hhu %.1hhu\nVectors: %.1f %.1f %.1f\nCoords: %.1f %.1f %.1f\n\n", scene->plane->color.r, scene->plane->color.g, scene->plane->color.b,  scene->plane->vectors.x, scene->plane->vectors.y, scene->plane->vectors.z, scene->plane->coords.x, scene->plane->coords.y, scene->plane->coords.z);
	if (scene->cylinder)
		printf("Cylinder:\nColors: %.1hhu %.1hhu %.1hhu\nVectors: %.1f %.1f %.1f\nCoords: %.1f %.1f %.1f\nDiameter: %.1f\nHeight: %.1f\n\n", scene->cylinder->color.r, scene->cylinder->color.g, scene->cylinder->color.b,  scene->cylinder->vectors.x, scene->cylinder->vectors.y, scene->cylinder->vectors.z, scene->cylinder->coords.x, scene->cylinder->coords.y, scene->cylinder->coords.z, scene->cylinder->diameter, scene->cylinder->height);
}