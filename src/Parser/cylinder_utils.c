/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:34:34 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/26 10:18:24 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	validate_cylinder_identifier(char *line, int *i, t_scene *scene)
{
	skip_whitespace(line, i);
	if (line[*i] != 'c' || line[*i + 1] != 'y')
		error("Missing 'cy' identifier for cylinder", scene);
	*i += 2;
}

float	parse_float(char *line, int *i, char *error_message,t_scene *scene)
{
	int	start;

	start = *i;
	while (line[*i] && (ft_isdigit(line[*i])
			|| line[*i] == '.' || line[*i] == '-' || line[*i] == '+'))
		(*i)++;
	if (start == *i)
		error(error_message, scene);
	return (ft_atof(&line[start]));
}

void	parse_center(char *line, int *i, t_cylinder *cylinder, t_scene *scene)
{
	cylinder->center.x = parse_float(line, i,
			"Invalid character in cylinder definition",scene);
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	cylinder->center.y = parse_float(line, i,
			"Invalid character in cylinder definition",scene);
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	cylinder->center.z = parse_float(line, i,
			"Invalid character in cylinder definition",scene);
}

void	parse_axis(char *line, int *i, t_cylinder *cylinder,t_scene *scene)
{
	cylinder->axis.x = parse_float(line, i,
			"Invalid character in cylinder definition", scene);
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	cylinder->axis.y = parse_float(line, i,
			"Invalid character in cylinder definition", scene);
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	cylinder->axis.z = parse_float(line, i,
			"Invalid character in cylinder definition", scene);
}
