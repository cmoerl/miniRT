/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spheres.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:50:01 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/05 09:22:16 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void parse_sphere(char *line, t_sphere **spheres)
{
    int i = 2; // Start after 'sp'
    t_sphere *sphere = malloc(sizeof(t_sphere));
    if (!sphere)
        error("Memory allocation failed", NULL);

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse center
    sphere->center.x = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != ','))
        i++;
    if (line[i] == ',') i++;

    sphere->center.y = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != ','))
        i++;
    if (line[i] == ',') i++;

    sphere->center.z = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t'))
        i++;

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse radius
    sphere->radius = ft_atof(&line[i]) / 2;
    while (line[i] && (line[i] != ' ' && line[i] != '\t'))
        i++;

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse RGB values
    int r = ft_atoi(&line[i]);
    while (line[i] && line[i] != ',')
        i++;
    if (line[i] == ',') i++;

    int g = ft_atoi(&line[i]);
    while (line[i] && line[i] != ',')
        i++;
    if (line[i] == ',') i++;

    int b = ft_atoi(&line[i]);

    // Validate RGB values
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
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