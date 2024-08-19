/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_planes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:47:53 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/19 11:34:35 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void parse_plane(char *line, t_plane **planes) {
    int i = 0; // Start at the beginning of the line

    // Skip leading whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Check for 'pl' identifier
    if (line[i] != 'p' || line[i + 1] != 'l') {
        error("Missing 'pl' identifier for plane", NULL);
    }
    i += 2; // Move past 'pl'

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse point
    t_plane *plane = malloc(sizeof(t_plane));
    if (!plane)
        error("Memory allocation failed", NULL);

    // Parse X coordinate of the point
    int start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i) {
        error("Invalid character in plane definition", NULL);
    }
    plane->point.x = ft_atof(&line[start]);

    if (line[i] == ',') i++;
    // Parse Y coordinate of the point
    start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i) {
        error("Invalid character in plane definition", NULL);
    }
    plane->point.y = ft_atof(&line[start]);

    if (line[i] == ',') i++;
    // Parse Z coordinate of the point
    start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i) {
        error("Invalid character in plane definition", NULL);
    }
    plane->point.z = ft_atof(&line[start]);

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse X axis
    start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i) {
        error("Invalid character in plane definition", NULL);
    }
    plane->axis.x = ft_atof(&line[start]);

    if (line[i] == ',') i++;
    // Parse Y axis
    start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i) {
        error("Invalid character in plane definition", NULL);
    }
    plane->axis.y = ft_atof(&line[start]);

    if (line[i] == ',') i++;
    // Parse Z axis
    start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i) {
        error("Invalid character in plane definition", NULL);
    }
    plane->axis.z = ft_atof(&line[start]);

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse RGB values
    start = i;
    while (line[i] && ft_isdigit(line[i]))
        i++;
    if (start == i) {
        error("Invalid character in plane definition", NULL);
    }
    int r = ft_atoi(&line[start]);

    if (line[i] == ',') i++;
    start = i;
    while (line[i] && ft_isdigit(line[i]))
        i++;
    if (start == i) {
        error("Invalid character in plane definition", NULL);
    }
    int g = ft_atoi(&line[start]);

    if (line[i] == ',') i++;
    start = i;
    while (line[i] && ft_isdigit(line[i]))
        i++;
    if (start == i) {
        error("Invalid character in plane definition", NULL);
    }
    int b = ft_atoi(&line[start]);

    // Validate RGB values
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        free(plane);
        error("Plane color values out of range [0, 255]", NULL);
    }
    plane->color.r = r / 255.0;
    plane->color.g = g / 255.0;
    plane->color.b = b / 255.0;

    // Skip any trailing whitespace or newline characters
    while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
        i++;

    // Check if there are any unexpected characters after the expected values
    if (line[i] != '\0') {
        free(plane);
        error("Invalid character in plane definition", NULL);
    }

    // Add plane to the linked list of planes
    plane->next = *planes;
    *planes = plane;
}
