/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:37:07 by panger            #+#    #+#             */
/*   Updated: 2024/02/26 12:32:15 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_file(char *file_path);
t_scene	*parse_lines(int fd);

t_scene	*parsing_hub(int argc, char **argv)
{
	int		fd;
	t_scene	*scene;

	if (argc < 1)
		return (NULL);
	fd = get_file(argv[0]);
	if (fd == -1)
		return (NULL);
	scene = parse_lines(fd);
	if (!scene)
		return (NULL);
	if (scene->ambient_light == NULL || scene->camera == NULL
		|| scene->light == NULL)
	{
		write(2, "Scene must have at least one A, C and L identifier\n", 49);
		return (free_scene(scene), NULL);
	}
	return (scene);
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

int	redirect_line(char *str, t_scene *scene, size_t line)
{
	char	**line_tab;
	int		error_status;

	line_tab = ft_split(str, " \t");
	if (!line_tab)
		return (-1);
	if (ft_strcmp(line_tab[0], "A") == 0 && scene->ambient_light == NULL)
		scene->ambient_light = ambient_identifier(line_tab, &error_status);
	else if (ft_strcmp(line_tab[0], "C") == 0 && scene->camera == NULL)
		scene->camera = camera_identifier(line_tab, &error_status);
	else if (ft_strcmp(line_tab[0], "L") == 0 && scene->light == NULL)
		scene->light = light_identifier(line_tab, &error_status);
	else if (ft_strcmp(line_tab[0], "sp") == 0)
		ft_sphere_addback(&(scene->sphere), sphere_identifier(line_tab, &error_status));
	else if (ft_strcmp(line_tab[0], "pl") == 0)
		ft_plane_addback(&(scene->plane), plane_identifier(line_tab, &error_status));
	else if (ft_strcmp(line_tab[0], "cy") == 0)
		ft_cylinder_addback(&(scene->cylinder), cylinder_identifier(line_tab, &error_status));
	else
		return (error_parsing(1, line, line_tab[0]), free_arr(line_tab), -1);
	if (error_status != 0)
		return (error_parsing(error_status, line, line_tab[0]), free_arr(line_tab), -1);
	return (free_arr(line_tab), 0);
}

t_scene	*parse_lines(int fd)
{
	char	*line;
	t_scene	*scene;
	size_t	i;

	scene = init_scene();
	if (!scene)
		return (NULL);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		if (ft_strcmp(line, "\n") != 0)
		{
			if (redirect_line(line, scene, i) == -1)
				return (free_scene(scene), NULL);
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (scene);
}
