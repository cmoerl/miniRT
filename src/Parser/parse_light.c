/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 23:32:14 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/04 23:35:26 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void parse_light(char *line, t_light *light)
{
    int i = 1; // Start after 'L'
    int r, g, b;

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse position
    light->position.x = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != ','))
        i++;
    if (line[i] == ',') i++;

    light->position.y = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != ','))
        i++;
    if (line[i] == ',') i++;

    light->position.z = ft_atof(&line[i]);
    while (line[i] && (line[i] != ' ' && line[i] != '\t'))
        i++;

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse intensity
    light->intensity = ft_atof(&line[i]);
    if (light->intensity < 0.0 || light->intensity > 1.0)
    {
        error("Light intensity out of range [0.0, 1.0]", NULL);
    }

    // Skip to RGB values if present
    while (line[i] && (line[i] != ' ' && line[i] != '\t'))
        i++;
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse RGB values (if present)
    if (line[i])
    {
        r = ft_atoi(&line[i]);
        while (line[i] && line[i] != ',')
            i++;
        if (line[i] == ',') i++;

        g = ft_atoi(&line[i]);
        while (line[i] && line[i] != ',')
            i++;
        if (line[i] == ',') i++;

        b = ft_atoi(&line[i]);

        // Validate RGB values
        if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        {
            error("Light color values out of range [0, 255]", NULL);
        }
    }
    else
    {
        r = 255;
        g = 255;
        b = 255;
    }

    printf("Parsed light position: %f, %f, %f\n", light->position.x, light->position.y, light->position.z);
    printf("Parsed light intensity: %f\n", light->intensity);
    printf("Parsed light color: %d, %d, %d\n", r, g, b);
}