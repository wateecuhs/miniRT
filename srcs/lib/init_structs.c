/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:32:06 by panger            #+#    #+#             */
/*   Updated: 2024/02/02 10:51:46 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_scene	*init_scene(void)
{
	t_scene	*ret;

	ret = (t_scene *)malloc(sizeof(t_scene));
	if (!ret)
		return (NULL);
	ret->ambient_light = NULL;
	ret->camera = NULL;
	ret->light = NULL;
	ret->cylinder = NULL;
	ret->sphere = NULL;
	ret->plane = NULL;
	return (ret);
}