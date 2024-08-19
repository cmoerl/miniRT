/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spheres.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:50:01 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/19 11:35:12 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void parse_sphere(char *line, t_sphere **spheres) {
    int i = 0; // Start at the beginning of the line

    // Skip leading whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Check for 'sp' identifier
    if (line[i] != 's' || line[i + 1] != 'p') {
        error("Missing 'sp' identifier for sphere", NULL);
    }
    i += 2; // Move past 'sp'

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse center
    t_sphere *sphere = malloc(sizeof(t_sphere));
    if (!sphere)
        error("Memory allocation failed", NULL);

    // Parse X coordinate of the center
    int start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i) {
        error("Invalid character in sphere definition", NULL);
    }
    sphere->center.x = ft_atof(&line[start]);

    if (line[i] == ',') i++;
    // Parse Y coordinate of the center
    start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i) {
        error("Invalid character in sphere definition", NULL);
    }
    sphere->center.y = ft_atof(&line[start]);

    if (line[i] == ',') i++;
    // Parse Z coordinate of the center
    start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i) {
        error("Invalid character in sphere definition", NULL);
    }
    sphere->center.z = ft_atof(&line[start]);

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse radius
    start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i) {
        error("Invalid character in sphere definition", NULL);
    }
    sphere->radius = ft_atof(&line[start]) / 2;
    if (sphere->radius <= 0) {
        error("Sphere radius must be positive", NULL);
    }

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse RGB values
    start = i;
    while (line[i] && ft_isdigit(line[i]))
        i++;
    if (start == i) {
        error("Invalid character in sphere definition", NULL);
    }
    int r = ft_atoi(&line[start]);

    if (line[i] == ',') i++;
    start = i;
    while (line[i] && ft_isdigit(line[i]))
        i++;
    if (start == i) {
        error("Invalid character in sphere definition", NULL);
    }
    int g = ft_atoi(&line[start]);

    if (line[i] == ',') i++;
    start = i;
    while (line[i] && ft_isdigit(line[i]))
        i++;
    if (start == i) {
        error("Invalid character in sphere definition", NULL);
    }
    int b = ft_atoi(&line[start]);

    // Validate RGB values
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        free(sphere);
        error("Sphere color values out of range [0, 255]", NULL);
    }
    sphere->color.r = r / 255.0;
    sphere->color.g = g / 255.0;
    sphere->color.b = b / 255.0;

    // Skip any trailing whitespace or newline characters
    while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
        i++;

    // Check if there are any unexpected characters after the expected values
    if (line[i] != '\0') {
        free(sphere);
        error("Invalid character in sphere definition", NULL);
    }

    // Add sphere to the linked list of spheres
    sphere->next = *spheres;
    *spheres = sphere;
}
