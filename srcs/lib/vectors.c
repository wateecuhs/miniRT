/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:42:50 by panger            #+#    #+#             */
/*   Updated: 2024/02/20 15:34:41 by panger           ###   ########.fr       */
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

t_vectors	add_coords_vectors(t_vectors coords, t_vectors vectors, double factor)
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

	res.x = p.x * m.m[0][0] + p.y * m.m[1][0] + p.z * m.m[2][0];
	res.y = p.x * m.m[0][1] + p.y * m.m[1][1] + p.z * m.m[2][1];
	res.z = p.x * m.m[0][2] + p.y * m.m[1][2] + p.z * m.m[2][2];
	return (res);
}

void	normalize_vector(t_vectors *vector)
{
	double len;

	len = sqrtf(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z);
	vector->x /= len;
	vector->y /= len;
	vector->z /= len;
}

double vec_dot(t_vectors vec1, t_vectors vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}


t_vectors	get_direction(int x, int y, t_scene *scene)
{
	double fov_coeff;
	double aspect_ratio;
	t_vectors	ret;

	fov_coeff = tan(((double)scene->camera->fov / 2) * (M_PI / 180));
	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	ret.x = ((2 * ((x + 0.5) / WIDTH)) - 1) * aspect_ratio * fov_coeff;
	ret.y = (1 - (2 * (y + 0.5) / HEIGHT)) * fov_coeff;
	ret.x *= -1;
	ret.z = 1;
	return (ret);
}


t_matrix	look_at(t_vectors origin, t_vectors cam_vector)
{
	t_matrix		m;
	t_vectors		tmp;
	t_vectors		right;
	t_vectors		forward;
	t_vectors		up;

	tmp = create_vector(0, 1, 0);
	forward = cam_vector;
	normalize_vector(&forward);
	if (forward.y == 1 || forward.y == -1)
	{
		if (forward.y == 1)
			right = create_vector(1, 0 ,0);
		else
			right = create_vector(-1, 0 ,0);
	}
	else
		right = cross_product(tmp, forward);
	up = cross_product(forward, right);
	m.m[0][0] = right.x;
	m.m[0][1] = right.y;
	m.m[0][2] = right.z;
	m.m[1][0] = up.x;
	m.m[1][1] = up.y;
	m.m[1][2] = up.z;
	m.m[2][0] = forward.x;
	m.m[2][1] = forward.y;
	m.m[2][2] = forward.z;
	return (m);
}

t_ray	ray_to_pixel(int x, int y, t_scene *scene)
{
	t_vectors	direction;
	t_matrix	c2w;

	direction = get_direction(x, y, scene);
	normalize_vector(&direction);
	// printf("for %d %d direction %f %f %f\n",x, y, direction.x, direction.y, direction.z);
	c2w = look_at(scene->camera->coords, scene->camera->vectors);
	direction = multiply_vec_matrix(direction, c2w);
	return (create_ray(scene->camera->coords, direction));
}
