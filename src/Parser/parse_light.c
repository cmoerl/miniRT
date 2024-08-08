/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 23:32:14 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/08 16:44:36 by marianfurni      ###   ########.fr       */
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
    int start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i)
    {
        error("Invalid character in light", NULL);
    }
    light->position.x = ft_atof(&line[start]);

    if (line[i] == ',') i++;
    start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i)
    {
        error("Invalid character in light", NULL);
    }
    light->position.y = ft_atof(&line[start]);

    if (line[i] == ',') i++;
    start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i)
    {
        error("Invalid character in light", NULL);
    }
    light->position.z = ft_atof(&line[start]);

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse intensity
    start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i)
    {
        error("Invalid character in light", NULL);
    }
    light->intensity = ft_atof(&line[start]);
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
        start = i;
        while (line[i] && ft_isdigit(line[i]))
            i++;
        if (start == i)
        {
            error("Invalid character in light", NULL);
        }
        r = ft_atoi(&line[start]);

        if (line[i] == ',') i++;
        start = i;
        while (line[i] && ft_isdigit(line[i]))
            i++;
        if (start == i)
        {
            error("Invalid character in light", NULL);
        }
        g = ft_atoi(&line[start]);

        if (line[i] == ',') i++;
        start = i;
        while (line[i] && ft_isdigit(line[i]))
            i++;
        if (start == i)
        {
            error("Invalid character in light", NULL);
        }
        b = ft_atoi(&line[start]);

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

    // Print parsed values in a clear format
    printf("Parsed Light:\n");
    printf("  Position: x=%f, y=%f, z=%f\n", light->position.x, light->position.y, light->position.z);
    printf("  Intensity: %f\n", light->intensity);
    printf("  Color: R=%d, G=%d, B=%d\n", r, g, b);
}