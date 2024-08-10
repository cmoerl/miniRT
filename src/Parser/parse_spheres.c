/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spheres.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:50:01 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/10 17:25:40 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"


void parse_sphere(char *line, t_sphere **spheres) {
    int i = 0; // Start at the beginning of the line

    // Skip leading whitespace
    skip_whitespace(line, &i);

    // Check for 'sp' identifier
    if (line[i] != 's' || line[i + 1] != 'p') {
        error("Missing 'sp' identifier for sphere", NULL);
    }
    i += 2; // Move past 'sp'

    // Skip whitespace
    skip_whitespace(line, &i);

    // Parse center
    t_sphere *sphere = malloc(sizeof(t_sphere));
    if (!sphere)
        error("Memory allocation failed", NULL);

    sphere->center.x = parse_float(line, &i);
    skip_whitespace(line, &i);
    if (line[i] == ',') i++;
    skip_whitespace(line, &i);
    sphere->center.y = parse_float(line, &i);
    skip_whitespace(line, &i);
    if (line[i] == ',') i++;
    skip_whitespace(line, &i);
    sphere->center.z = parse_float(line, &i);

    // Skip whitespace
    skip_whitespace(line, &i);

    // Parse radius
    sphere->radius = parse_float(line, &i) / 2;
    skip_whitespace(line, &i);

    // Parse RGB values
    int r = parse_color_component(line, &i);
    skip_whitespace(line, &i);
    if (line[i] == ',') i++;
    skip_whitespace(line, &i);
    int g = parse_color_component(line, &i);
    skip_whitespace(line, &i);
    if (line[i] == ',') i++;
    skip_whitespace(line, &i);
    int b = parse_color_component(line, &i);

    // Validate RGB values
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        free(sphere);
        error("Sphere color values out of range [0, 255]", NULL);
    }
    sphere->color.r = r / 255.0;
    sphere->color.g = g / 255.0;
    sphere->color.b = b / 255.0;

    // Add sphere to the linked list of spheres
    sphere->next = *spheres;
    *spheres = sphere;
}

