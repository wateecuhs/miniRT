/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:37:07 by panger            #+#    #+#             */
/*   Updated: 2024/02/01 13:00:06 by panger           ###   ########.fr       */
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
	return (0);
}

int	get_file(char *file_path)
{
	int	fd;
	int	extension_position;

	extension_position = ft_strrchr(file_path, '.');
	if (extension_position == -1 || ft_strcmp(&file_path[extension_position ], ".rt") != 0)
	{
		write(2, file_path, ft_strlen(file_path));
		write(2, "File must have .rt extension\n", 29);
		return (-1);
	}
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		perror(file_path);
	parse_lines(fd);
	return (fd);
}

int	redirect_line(char *str)
{
	size_t	i;
	int		identifier;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	identifier = ft_strchr(&str[i], ' ');
	if (identifier == -1)
		return (-1);
	if (ft_strncmp(&str[i], "A", identifier) == 0)
		return (1); //redirect towards ambient light line parser
	else if (ft_strncmp(&str[i], "C", identifier) == 0)
		return (2); //redirect towards camera line parser
	else if (ft_strncmp(&str[i], "L", identifier) == 0)
		return (3); //redirect towards light line parser
	else if (ft_strncmp(&str[i], "sp", identifier) == 0)
		return (4); //redirect towards sphere line parser
	else if (ft_strncmp(&str[i], "pl", identifier) == 0)
		return (5); //redirect towards plane line parser
	else if (ft_strncmp(&str[i], "cy", identifier) == 0)
		return (5); //redirect towards cylinder line parser
	else
		return (-1); // return null value
}

int	parse_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		printf("%d\n", redirect_line(line));
		free(line);
		line = get_next_line(fd);
	}
}
