/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcindrak <dcindrak@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:45:39 by panger            #+#    #+#             */
/*   Updated: 2024/02/27 12:24:25 by dcindrak         ###   ########.fr       */
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

t_vectors	get_direction(int x, int y, t_scene *scene)
{
	double		fov_coeff;
	double		aspect_ratio;
	t_vectors	ret;

	fov_coeff = tan(((double)scene->camera->fov / 2) * (M_PI / 180));
	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	ret.x = ((2 * ((x + 0.5) / WIDTH)) - 1) * aspect_ratio * fov_coeff;
	ret.y = (1 - (2 * (y + 0.5) / HEIGHT)) * fov_coeff;
	ret.x *= -1;
	ret.z = 1;
	return (ret);
}

t_matrix	look_at(t_vectors cam_vector)
{
	t_matrix		m;
	t_vectors		tmp;
	t_vectors		right;
	t_vectors		forward;
	t_vectors		up;

	tmp = create_vector(0, 1, 0);
	forward = cam_vector;
	vec_normalize(&forward);
	right = vec_cross_product(tmp, forward);
	if (forward.y == 1)
		right = create_vector(1, 0, 0);
	else if (forward.y == -1)
		right = create_vector(-1, 0, 0);
	up = vec_cross_product(forward, right);
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
	vec_normalize(&direction);
	c2w = look_at(scene->camera->vectors);
	direction = vec_matrix_mult(direction, c2w);
	return (create_ray(scene->camera->coords, direction));
}
