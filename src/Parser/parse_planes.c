/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_planes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:47:53 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/21 17:10:21 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_plane_axis(char *line, int *i, t_plane *plane)
{
	plane->axis.x = parse_coordinate(line, i,
			"Invalid character in plane definition");
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	plane->axis.y = parse_coordinate(line, i,
			"Invalid character in plane definition");
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	plane->axis.z = parse_coordinate(line, i,
			"Invalid character in plane definition");
}

int	parse_color_component(char *line, int *i, char *error_message)
{
	int	start;

	skip_whitespace(line, i);
	start = *i;
	while (line[*i] && ft_isdigit(line[*i]))
		(*i)++;
	if (start == *i)
		error(error_message, NULL);
	return (ft_atoi(&line[start]));
}

void	parse_plane_color(char *line, int *i, t_plane *plane)
{
	int	r;
	int	g;
	int	b;

	r = parse_color_component(line, i, "Invalid character in plane definition");
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	g = parse_color_component(line, i, "Invalid character in plane definition");
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	b = parse_color_component(line, i, "Invalid character in plane definition");
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error("Plane color values out of range [0, 255]", NULL);
	plane->color.r = r / 255.0;
	plane->color.g = g / 255.0;
	plane->color.b = b / 255.0;
}

void parse_plane(char *line, t_plane **planes)
{
	int		i;
	t_plane	*plane;

	i = 0;
	skip_whitespace(line, &i);
	validate_plane_identifier(line, &i);
	skip_whitespace(line, &i);
	plane = malloc(sizeof(t_plane));
	if (!plane)
		error("Memory allocation failed", NULL);
	parse_plane_coordinates(line, &i, plane);
	skip_whitespace(line, &i);
	parse_plane_axis(line, &i, plane);
	skip_whitespace(line, &i);
	parse_plane_color(line, &i, plane);
	skip_whitespace(line, &i);
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	if (line[i] != '\0')
	{
		free(plane);
		error("Invalid character in plane definition", NULL);
	}
	plane->next = *planes;
	*planes = plane;
}
