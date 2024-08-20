/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:16:33 by mafurnic          #+#    #+#             */
/*   Updated: 2024/08/20 13:18:01 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

// Helper function to validate identifier
void	validate_identifier_light(char actual, char expected)
{
	if (actual != expected)
		error("Invalid identifier", NULL);
}

// Helper function to parse a float value
float	parse_float(char *line, int *i)
{
	int	start;

	start = *i;
	while (line[*i] && (ft_isdigit(line[*i])
			|| line[*i] == '.' || line[*i] == '-' || line[*i] == '+'))
		(*i)++;
	if (start == *i)
		error("Invalid character in light definition", NULL);
	return (ft_atof(&line[start]));
}

// Helper function to parse a vector
t_vector	parse_vector_light(char *line, int *i)
{
	t_vector	vec;

	vec.x = parse_float(line, i);
	if (line[*i] == ',')
		(*i)++;
	vec.y = parse_float(line, i);
	if (line[*i] == ',')
		(*i)++;
	vec.z = parse_float(line, i);
	return (vec);
}
