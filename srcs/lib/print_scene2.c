/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcindrak <dcindrak@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:34:01 by dcindrak          #+#    #+#             */
/*   Updated: 2024/02/27 13:38:08 by dcindrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_light(t_light *light)
{
	if (light)
		printf("Light:\nColors: %.1hhu %.1hhu %.1hhu\nBrightness: \
		%.1f\nCoords: %.1f %.1f %.1f\n\n", light->color.r, light->color.g, \
		light->color.b, light->brightness, light->coords.x, \
		light->coords.y, light->coords.z);
}

void	print_camera(t_camera *camera)
{
	if (camera)
		printf("Camera:\nVectors: %.1f %.1f %.1f\nFov: %.1hhu\nCoords: \
		%.1f %.1f %.1f\n\n", camera->vectors.x, camera->vectors.y, \
		camera->vectors.z, camera->fov, camera->coords.x, \
		camera->coords.y, camera->coords.z);
}

void	print_sphere(t_sphere *sp)
{
	printf("Sphere:\nColors: %.1hhu %.1hhu %.1hhu\nDiameter: %.1f\nCoords: \
	%.1f %.1f %.1f\n\n", sp->color.r, sp->color.g, sp->color.b, \
	sp->diameter, sp->coords.x, sp->coords.y, sp->coords.z);
}

void	print_plane(t_plane *pl)
{
	printf("Plane:\nColors: %.1hhu %.1hhu %.1hhu\nVectors: %.1f %.1f %.1f\nCoords: \
	%.1f %.1f %.1f\n\n", pl->color.r, pl->color.g, pl->color.b, pl->vectors.x, \
	pl->vectors.y, pl->vectors.z, pl->coords.x, pl->coords.y, pl->coords.z);
}

void	print_cylinder(t_cylinder *cy)
{
	printf("Cylinder:\nColors: %.1hhu %.1hhu %.1hhu\nVectors: %.1f %.1f %.1f\nCoords: %.1f %.1f %.1f\nDiameter: \
	%.1f\nHeight: %.1f\n\n", cy->color.r, cy->color.g, cy->color.b, \
	cy->vectors.x, cy->vectors.y, cy->vectors.z, cy->coords.x, \
	cy->coords.y, cy->coords.z, cy->diameter, cy->height);
}
