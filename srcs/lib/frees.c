/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:31:09 by panger            #+#    #+#             */
/*   Updated: 2024/02/27 16:35:10 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_object(t_scene *scene)
{
	void	*tmp;

	while (scene->sphere)
	{
		tmp = scene->sphere->next;
		free(scene->sphere);
		scene->sphere = tmp;
	}
	while (scene->plane)
	{
		tmp = scene->plane->next;
		free(scene->plane);
		scene->plane = tmp;
	}
	while (scene->cylinder)
	{
		tmp = scene->cylinder->next;
		free(scene->cylinder);
		scene->cylinder = tmp;
	}
}

void	free_scene(t_scene *scene)
{
	if (scene->ambient_light)
		free(scene->ambient_light);
	if (scene->light)
		free(scene->light);
	if (scene->camera)
		free(scene->camera);
	free_object(scene);
	free(scene);
}
