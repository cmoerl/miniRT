/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spheres.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:50:01 by marianfurni       #+#    #+#             */
/*   Updated: 2024/09/03 13:25:07 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	validate_sphere_identifier(char *line, int *i, t_scene *scene)
{
    skip_whitespace(line, i);
    if (line[*i] != 's' || line[*i + 1] != 'p')
        error("Missing 'sp' identifier for sphere", scene, line);
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
        error("Sphere radius must be positive", scene, line);
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
    t_sphere	*new_sphere;

    i = 0;
    validate_line_format(line, scene); // Validate the line format first
    skip_whitespace(line, &i);
    validate_sphere_identifier(line, &i, scene);
    skip_whitespace(line, &i);
    new_sphere = malloc(sizeof(t_sphere));
    if (!new_sphere)
    {
        error("Memory allocation failed", scene, line);
    }
    add_sphere_to_list(spheres, new_sphere);
    parse_sphere_properties(line, &i, new_sphere, scene);
    while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
    {
        i++;
    }
    if (line[i] != '\0')
    {
        error("Invalid character in sphere definition", scene, line);
    }
}
