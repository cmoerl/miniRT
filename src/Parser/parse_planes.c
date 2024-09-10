/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_planes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:47:53 by marianfurni       #+#    #+#             */
/*   Updated: 2024/09/10 16:38:29 by marianfurni      ###   ########.fr       */
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
	if (plane->axis.x < -1 || plane->axis.x > 1
		|| plane->axis.y < -1 || plane->axis.y > 1
		|| plane->axis.z < -1 || plane->axis.z > 1)
		error("Plane axis values out of range [-1, 1]", scene, line);
	// plane->axis = normalise_vector(plane->axis);
}

int	parse_color_component(char *line, int *i,
		char *error_message, t_scene *scene)
{
	int	start;

	skip_whitespace(line, i);
	start = *i;
	if (line[*i] == '+')
		(*i)++;
	while (line[*i] && ft_isdigit(line[*i]))
		(*i)++;
	if (start == *i)
		error(error_message, scene, line);
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
		error("Plane color values out of range [0, 255]", scene, line);
	plane->color.r = r;
	plane->color.g = g;
	plane->color.b = b;
}

void	add_plane_to_list(t_plane **planes, t_plane *new_plane)
{
	t_plane	*current;

	new_plane->next = NULL;
	if (*planes == NULL)
	{
		*planes = new_plane;
	}
	else
	{
		current = *planes;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_plane;
	}
}

void	parse_plane(char *line, t_plane **planes, t_scene *scene)
{
	int		i;
	t_plane	*new_plane;

	i = 0;
	validate_line_format(line, scene);
	skip_whitespace(line, &i);
	validate_plane_identifier(line, &i, scene);
	skip_whitespace(line, &i);
	new_plane = malloc(sizeof(t_plane));
	if (!new_plane)
		error("Memory allocation failed", scene, line);
	add_plane_to_list(planes, new_plane);
	parse_plane_coordinates(line, &i, new_plane, scene);
	skip_whitespace(line, &i);
	parse_plane_axis(line, &i, new_plane, scene);
	skip_whitespace(line, &i);
	parse_plane_color(line, &i, new_plane, scene);
	skip_whitespace(line, &i);
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
	{
		i++;
	}
	if (line[i] != '\0')
		error("Invalid character in plane definition", scene, line);
}
