/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_planes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:47:53 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/10 17:25:55 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void parse_plane(char *line, t_plane **planes) {
    int i = 0; // Start at the beginning of the line

    // Skip leading whitespace
    skip_whitespace(line, &i);

    // Check for 'pl' identifier
    if (line[i] != 'p' || line[i + 1] != 'l') {
        error("Missing 'pl' identifier for plane", NULL);
    }
    i += 2; // Move past 'pl'

    // Skip whitespace
    skip_whitespace(line, &i);

    // Parse point
    t_plane *plane = malloc(sizeof(t_plane));
    if (!plane)
        error("Memory allocation failed", NULL);

    plane->point.x = parse_float(line, &i);
    skip_whitespace(line, &i);
    if (line[i] == ',') i++;
    skip_whitespace(line, &i);
    plane->point.y = parse_float(line, &i);
    skip_whitespace(line, &i);
    if (line[i] == ',') i++;
    skip_whitespace(line, &i);
    plane->point.z = parse_float(line, &i);

    // Skip whitespace
    skip_whitespace(line, &i);

    // Parse axis
    plane->axis.x = parse_float(line, &i);
    skip_whitespace(line, &i);
    if (line[i] == ',') i++;
    skip_whitespace(line, &i);
    plane->axis.y = parse_float(line, &i);
    skip_whitespace(line, &i);
    if (line[i] == ',') i++;
    skip_whitespace(line, &i);
    plane->axis.z = parse_float(line, &i);

    // Skip whitespace
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
        free(plane);
        error("Plane color values out of range [0, 255]", NULL);
    }
    plane->color.r = r / 255.0;
    plane->color.g = g / 255.0;
    plane->color.b = b / 255.0;

    // Add plane to the linked list of planes
    plane->next = *planes;
    *planes = plane;
}
 