/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_operations3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:50:54 by dcindrak          #+#    #+#             */
/*   Updated: 2024/02/27 16:34:07 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	vec_len(t_vectors v)
{
	return (sqrt(vec_dot(v, v)));
}

double	vec_cos(t_vectors a, t_vectors b)
{
	return (vec_dot(a, b) / (vec_len(a) * vec_len(b)));
}

double	vec_dot(t_vectors vec1, t_vectors vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}
