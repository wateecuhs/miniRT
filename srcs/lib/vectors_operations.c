/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:42:50 by panger            #+#    #+#             */
/*   Updated: 2024/02/12 19:01:49 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vectors	create_vector(float x, float y, float z)
{
	t_vectors	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_vectors	cross_product(t_vectors vec1, t_vectors vec2)
{
	t_vectors result;

	result.x = vec1.y * vec2.z - vec1.z * vec2.y;
	result.y = vec1.z * vec2.x - vec1.x * vec2.z;
	result.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (result);
}

t_vectors	substract(t_vectors vec1, t_vectors vec2)
{
	t_vectors result;

	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	result.z = vec1.z - vec2.z;
	return (result);
}

t_matrix	look_at(t_vectors origin, t_vectors cam_vector)
{
	t_matrix		m;
	t_vectors		random;
	t_vectors		right;
	t_vectors		up;

	random = create_vector(0, 1, 0);
	// printf("NORMALIZING RANDOM\n");
	normalize_vector(&random);
	right = cross_product(random, cam_vector);
	// printf("NORMALIZING RIGHT\n");
	normalize_vector(&right);
	up = cross_product(cam_vector, right);
	// printf("NORMALIZING UP\n");
	// printf("up %f %f %f\n", up.x, up.y, up.z);
	normalize_vector(&up);
	m.matrix[0][0] = right.x;
	m.matrix[0][1] = right.y;
	m.matrix[0][2] = right.z;
	m.matrix[1][0] = up.x;
	m.matrix[1][1] = up.y;
	m.matrix[1][2] = up.z;
	m.matrix[2][0] = cam_vector.x;
	m.matrix[2][1] = cam_vector.y;
	m.matrix[2][2] = cam_vector.z;
	m.matrix[3][0] = origin.x;
	m.matrix[3][1] = origin.y;
	m.matrix[3][2] = origin.z;
	return (m);
}
