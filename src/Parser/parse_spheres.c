/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spheres.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:50:01 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/26 12:29:37 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	validate_sphere_identifier(char *line, int *i, t_scene *scene)
{
	skip_whitespace(line, i);
	if (line[*i] != 's' || line[*i + 1] != 'p')
		error("Missing 'sp' identifier for sphere", scene);
	*i += 2;
}

void	parse_center_sphere(char *line, int *i,
			t_sphere *sphere, t_scene *scene)
{
	sphere->center.x = parse_float(line, i,
			"Invalid character in sphere definition", scene);
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	sphere->center.y = parse_float(line, i,
			"Invalid character in sphere definition", scene);
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	sphere->center.z = parse_float(line, i,
			"Invalid character in sphere definition", scene);
}

void	parse_radius_sphere(char *line, int *i,
			t_sphere *sphere, t_scene *scene)
{
	sphere->radius = parse_float(line, i,
			"Invalid character in sphere definition", scene) / 2;
	if (sphere->radius <= 0)
		error("Sphere radius must be positive", NULL);
}

void	parse_sphere_properties(char *line, int *i,
			t_sphere *sphere, t_scene *scene)
{
	skip_whitespace(line, i);
	parse_center_sphere(line, i, sphere, scene);
	skip_whitespace(line, i);
	parse_radius_sphere(line, i, sphere, scene);
	skip_whitespace(line, i);
	parse_color_sphere(line, i, sphere, scene);
	skip_whitespace(line, i);
}

void	parse_sphere(char *line, t_sphere **spheres, t_scene *scene)
{
	int			i;
	t_sphere	*sphere;

	i = 0;
	skip_whitespace(line, &i);
	validate_sphere_identifier(line, &i, scene);
	skip_whitespace(line, &i);
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		error("Memory allocation failed", NULL);
	parse_sphere_properties(line, &i, sphere, scene);
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	if (line[i] != '\0')
	{
		free(sphere);
		error("Invalid character in sphere definition", scene);
	}
	sphere->next = *spheres;
	*spheres = sphere;
}
