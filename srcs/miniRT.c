/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:58:52 by panger            #+#    #+#             */
/*   Updated: 2024/02/20 16:11:37 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_scene	*scene;

	if (argc < 2)
		return (1);
	scene = parsing_hub(argc - 1, &argv[1]);
	if (!scene)
		return (1);
	init(scene);
	return (0);
}
