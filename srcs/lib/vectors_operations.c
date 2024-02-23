/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:42:50 by panger            #+#    #+#             */
/*   Updated: 2024/02/23 14:23:27 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vectors	create_vector(double x, double y, double z)
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

t_vectors	multiply_vector(t_vectors vec1, double factor)
{
	t_vectors result;

	result.x = vec1.x * factor;
	result.y = vec1.y * factor;
	result.z = vec1.z * factor;
	return (result);
}
