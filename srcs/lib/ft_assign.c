/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assign.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:36:55 by panger            #+#    #+#             */
/*   Updated: 2024/02/20 13:00:10 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_pair	assign_pair(double x, double y)
{
	t_pair	ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}
