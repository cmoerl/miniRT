/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spheres.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:50:01 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/28 08:41:35 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	validate_sphere_identifier(char *line, int *i)
{
	skip_whitespace(line, i);
	if (line[*i] != 's' || line[*i + 1] != 'p')
		error("Missing 'sp' identifier for sphere", NULL);
	*i += 2;
}

void	parse_center_sphere(char *line, int *i, t_sphere *sphere)
{
	sphere->center.x = parse_float(line, i,
			"Invalid character in sphere definition");
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	sphere->center.y = parse_float(line, i,
			"Invalid character in sphere definition");
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	sphere->center.z = parse_float(line, i,
			"Invalid character in sphere definition");
}

void	parse_radius_sphere(char *line, int *i, t_sphere *sphere)
{
	sphere->radius = parse_float(line, i,
			"Invalid character in sphere definition") / 2;
	if (sphere->radius <= 0)
		error("Sphere radius must be positive", NULL);
}

void	parse_sphere_properties(char *line, int *i, t_sphere *sphere)
{
	skip_whitespace(line, i);
	parse_center_sphere(line, i, sphere);
	skip_whitespace(line, i);
	parse_radius_sphere(line, i, sphere);
	skip_whitespace(line, i);
	parse_color_sphere(line, i, sphere);
	skip_whitespace(line, i);
}

void	parse_sphere(char *line, t_sphere **spheres)
{
	int			i;
	t_sphere	*sphere;

	i = 0;
	skip_whitespace(line, &i);
	validate_sphere_identifier(line, &i);
	skip_whitespace(line, &i);
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		error("Memory allocation failed", NULL);
	parse_sphere_properties(line, &i, sphere);
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	if (line[i] != '\0')
	{
		free(sphere);
		error("Invalid character in sphere definition", NULL);
	}
	sphere->next = *spheres;
	*spheres = sphere;
}
