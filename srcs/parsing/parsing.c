/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:37:07 by panger            #+#    #+#             */
/*   Updated: 2024/02/05 11:23:39 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_file(char *file_path);
int	parse_lines(int fd);

int	parsing_hub(int argc, char **argv)
{
	int	fd;

	if (argc < 1)
		return (-1);
	fd = get_file(argv[0]);
	if (fd == -1)
		return (-1);
	parse_lines(fd);
	return (0);
}

int	get_file(char *file_path)
{
	int	fd;
	int	extension_position;

	extension_position = ft_strrchr(file_path, '.');
	if (extension_position == -1
		|| ft_strcmp(&file_path[extension_position], ".rt") != 0)
	{
		write(2, file_path, ft_strlen(file_path));
		write(2, "File must have .rt extension\n", 29);
		return (-1);
	}
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		perror(file_path);
	return (fd);
}

int	redirect_line(char *str, t_scene *scene)
{
	size_t	i;
	int		identifier;
	char	**line_tab;

	line_tab = ft_split(str, " ");
	if (!line_tab)
		return (-1);
	if (ft_strcmp(line_tab[0], "A") == 0)
		scene->ambient_light = ambient_identifier(line_tab);
	else if (ft_strcmp(line_tab[0], "C") == 0)
		scene->camera = camera_identifier(line_tab);
	else if (ft_strcmp(line_tab[0], "L") == 0)
		scene->light = light_identifier(line_tab);
	else if (ft_strcmp(line_tab[0], "sp") == 0)
		ft_sphere_addback(&(scene->sphere), sphere_identifier(line_tab));
	else if (ft_strcmp(line_tab[0], "pl") == 0)
		ft_plane_addback(&(scene->plane), plane_identifier(line_tab));
	else if (ft_strcmp(line_tab[0], "cy") == 0)
		ft_cylinder_addback(&(scene->cylinder), cylinder_identifier(line_tab));
	else
		return (free_arr(line_tab), -1);
	free_arr(line_tab);
}

int	parse_lines(int fd)
{
	char	*line;
	t_scene	*scene;

	scene = init_scene();
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strcmp(line, "\n") != 0)
			redirect_line(line, scene);
		free(line);
		line = get_next_line(fd);
	}
	print_scene(scene);
	free_scene(scene);
}
