/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:34:34 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/21 17:48:58 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	validate_cylinder_identifier(char *line, int *i)
{
	skip_whitespace(line, i);
	if (line[*i] != 'c' || line[*i + 1] != 'y')
		error("Missing 'cy' identifier for cylinder", NULL);
	*i += 2;
}

float	parse_float(char *line, int *i, char *error_message)
{
	int	start;

	start = *i;
	while (line[*i] && (ft_isdigit(line[*i])
			|| line[*i] == '.' || line[*i] == '-' || line[*i] == '+'))
		(*i)++;
	if (start == *i)
		error(error_message, NULL);
	return (ft_atof(&line[start]));
}

void	parse_center(char *line, int *i, t_cylinder *cylinder)
{
	cylinder->center.x = parse_float(line, i,
			"Invalid character in cylinder definition");
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	cylinder->center.y = parse_float(line, i,
			"Invalid character in cylinder definition");
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	cylinder->center.z = parse_float(line, i,
			"Invalid character in cylinder definition");
}

void	parse_axis(char *line, int *i, t_cylinder *cylinder)
{
	cylinder->axis.x = parse_float(line, i,
			"Invalid character in cylinder definition");
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	cylinder->axis.y = parse_float(line, i,
			"Invalid character in cylinder definition");
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	cylinder->axis.z = parse_float(line, i,
			"Invalid character in cylinder definition");
}
