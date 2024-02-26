/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_operations2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:42:50 by panger            #+#    #+#             */
/*   Updated: 2024/02/26 13:01:07 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vectors	vec_add(t_vectors coords, t_vectors vectors, double factor)
{
	t_vectors	ret;

	ret.x = coords.x + (vectors.x * factor);
	ret.y = coords.y + (vectors.y * factor);
	ret.z = coords.z + (vectors.z * factor);
	return (ret);
}

t_vectors	vec_matrix_mult(t_vectors p, t_matrix m)	
{
	t_vectors res;

	res.x = p.x * m.m[0][0] + p.y * m.m[1][0] + p.z * m.m[2][0];
	res.y = p.x * m.m[0][1] + p.y * m.m[1][1] + p.z * m.m[2][1];
	res.z = p.x * m.m[0][2] + p.y * m.m[1][2] + p.z * m.m[2][2];
	return (res);
}

void	vec_normalize(t_vectors *vector)
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