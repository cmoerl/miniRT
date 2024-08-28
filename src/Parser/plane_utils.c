/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:45:00 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/28 15:48:22 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	validate_plane_identifier(char *line, int *i, t_scene *scene)
{
	skip_whitespace(line, i);
	if (line[*i] != 'p' || line[*i + 1] != 'l')
		error("Missing 'pl' identifier for plane", scene, line);
	*i += 2;
}

float	parse_coordinate(char *line, int *i,
		char *error_message, t_scene *scene)
{
	int	start;

	skip_whitespace(line, i);
	start = *i;
	while (line[*i] && (ft_isdigit(line[*i])
			|| line[*i] == '.' || line[*i] == '-' || line[*i] == '+'))
		(*i)++;
	if (start == *i)
		error(error_message, scene, line);
	return (ft_atof(&line[start]));
}

void	parse_plane_coordinates(char *line, int *i,
		t_plane *plane, t_scene *scene)
{
	plane->point.x = parse_coordinate(line, i,
			"Invalid character in plane definition", scene);
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	plane->point.y = parse_coordinate(line, i,
			"Invalid character in plane definition", scene);
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	plane->point.z = parse_coordinate(line, i,
			"Invalid character in plane definition", scene);
}
