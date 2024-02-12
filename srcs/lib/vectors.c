/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:42:50 by panger            #+#    #+#             */
/*   Updated: 2024/02/12 19:08:52 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	create_ray(t_vectors origin, t_vectors direction)
{
	t_ray	ret;

	ret.origin = origin;
	ret.vector = direction;
	return (ret);
}

t_vectors	add_coords_vectors(t_vectors coords, t_vectors vectors, float factor)
{
	t_vectors	ret;

	ret.x = coords.x + (vectors.x * factor);
	ret.y = coords.y + (vectors.y * factor);
	ret.z = coords.z + (vectors.z * factor);
	return (ret);
}

t_vectors	multiply_vec_matrix(t_vectors p, t_matrix m)
{
	t_vectors res;

	res.x = p.x * m.matrix[0][0] + p.y * m.matrix[1][0]
		+ p.z * m.matrix[2][0] + m.matrix[3][0];
	res.y = p.x * m.matrix[0][1] + p.y * m.matrix[1][1]
		+ p.z * m.matrix[2][1] + m.matrix[3][1];
	res.z = p.x * m.matrix[0][2] + p.y * m.matrix[1][2]
		+ p.z * m.matrix[2][2] + m.matrix[3][2];
	return (res);
}

void	normalize_vector(t_vectors *vector)
{
	float len;

	len = sqrtf((float)powf(vector->x, 2) + (float)powf(vector->y, 2) + (float)powf(vector->z, 2));
	vector->x /= len;
	vector->y /= len;
	vector->z /= len;
}

t_vectors	get_direction(int x, int y, t_scene *scene)
{
	float fov_coeff;
	float aspect_ratio;
	float p_x;
	float p_y;

	fov_coeff = tan((float)scene->camera->fov / 2 * M_PI / 180);
	aspect_ratio = (float)WIDTH / (float)HEIGHT;
	p_x = (2 * (x + 0.5) / (float)WIDTH - 1) * aspect_ratio * fov_coeff;
	p_y = (1 - 2 * (y + 0.5) / (float)HEIGHT) * fov_coeff;
	return (create_vector(p_x, p_y, 1));
}

t_ray	ray_to_pixel(int x, int y, t_scene *scene)
{
	t_vectors	origin;
	t_vectors	direction;
	t_matrix	c2w;
	t_camera	camera;

	c2w = look_at(scene->camera->coords, scene->camera->vectors);
	origin = multiply_vec_matrix(create_vector(0, 0, 0), c2w);
	direction = get_direction(x, y, scene);
	direction = multiply_vec_matrix(direction, c2w);
	direction = substract(direction, scene->camera->coords);
	normalize_vector(&direction);
	return (create_ray(origin, direction));
}
