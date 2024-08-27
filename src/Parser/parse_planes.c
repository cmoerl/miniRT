/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_planes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:47:53 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/27 18:00:41 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_plane_axis(char *line, int *i, t_plane *plane, t_scene *scene)

{
	plane->axis.x = parse_coordinate(line, i,
			"Invalid character in plane definition", scene);
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	plane->axis.y = parse_coordinate(line, i,
			"Invalid character in plane definition", scene);
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	plane->axis.z = parse_coordinate(line, i,
			"Invalid character in plane definition", scene);
}

int	parse_color_component(char *line, int *i,
		char *error_message, t_scene *scene)
{
	int	start;

	skip_whitespace(line, i);
	start = *i;
	while (line[*i] && ft_isdigit(line[*i]))
		(*i)++;
	if (start == *i)
		error(error_message, scene);
	return (ft_atoi(&line[start]));
}

void	parse_plane_color(char *line, int *i, t_plane *plane, t_scene *scene)
{
	int	r;
	int	g;
	int	b;

	r = parse_color_component(line, i,
			"Invalid character in plane definition", scene);
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	g = parse_color_component(line, i,
			"Invalid character in plane definition", scene);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	b = parse_color_component(line, i,
			"Invalid character in plane definition", scene);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error("Plane color values out of range [0, 255]", scene);
	plane->color.r = r;
	plane->color.g = g;
	plane->color.b = b;
}

void	parse_plane(char *line, t_plane **planes, t_scene *scene)
{
	int		i;

	i = 0;
	skip_whitespace(line, &i);
	validate_plane_identifier(line, &i, scene);
	skip_whitespace(line, &i);
	scene->objects->planes = malloc(sizeof(t_plane));
	if (!scene->objects->planes)
		error("Memory allocation failed", scene);
	memset(scene->objects->planes, 0, sizeof(t_plane));
	parse_plane_coordinates(line, &i, scene->objects->planes, scene);
	skip_whitespace(line, &i);
	parse_plane_axis(line, &i, scene->objects->planes, scene);
	skip_whitespace(line, &i);
	parse_plane_color(line, &i, scene->objects->planes, scene);
	skip_whitespace(line, &i);
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	if (line[i] != '\0')
	{
		free(scene->objects->planes);
		error("Invalid character in plane definition", scene);
	}
	scene->objects->planes->next = *planes;
}
