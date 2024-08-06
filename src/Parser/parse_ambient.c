/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:41:08 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/06 08:00:32 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void parse_ambient(char *line, t_amblight *ambient)
{
    int i = 0; // Start at the beginning of the line
    float intensity;
    int r, g, b;

    // Skip leading whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    
    // Check for 'A' identifier
    if (line[i] != 'A')
    {
        error("Missing 'A' identifier for ambient lighting", NULL);
    }
    i++; // Move past 'A'

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    
    // Parse intensity
    int start = i;
    while (line[i] && (ft_isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '+'))
        i++;
    if (start == i)
    {
        error("Invalid character in ambient lighting intensity", NULL);
    }
    intensity = ft_atof(&line[start]);
    if (intensity < 0.0 || intensity > 1.0)
    {
        error("Ambient lighting intensity out of range [0.0, 1.0]", NULL);
    }
    printf("Parsed intensity: %f\n", intensity);

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Parse red value
    start = i;
    while (line[i] && ft_isdigit(line[i]))
        i++;
    if (start == i)
    {
        error("Invalid character in ambient lighting red value", NULL);
    }
    r = ft_atoi(&line[start]);
    if (r < 0 || r > 255)
    {
        error("Ambient lighting red value out of range [0, 255]", NULL);
    }
    printf("Parsed red: %d\n", r);

    // Skip whitespace and comma
    while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == ','))
        i++;

    // Parse green value
    start = i;
    while (line[i] && ft_isdigit(line[i]))
        i++;
    if (start == i)
    {
        error("Invalid character in ambient lighting green value", NULL);
    }
    g = ft_atoi(&line[start]);
    if (g < 0 || g > 255)
    {
        error("Ambient lighting green value out of range [0, 255]", NULL);
    }
    printf("Parsed green: %d\n", g);

    // Skip whitespace and comma
    while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == ','))
        i++;

    // Parse blue value
    start = i;
    while (line[i] && ft_isdigit(line[i]))
        i++;
    if (start == i)
    {
        error("Invalid character in ambient lighting blue value", NULL);
    }
    b = ft_atoi(&line[start]);
    if (b < 0 || b > 255)
    {
        error("Ambient lighting blue value out of range [0, 255]", NULL);
    }
    printf("Parsed blue: %d\n", b);

    // Skip any trailing whitespace or newline characters
    while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
        i++;

    // Check if there are any unexpected characters after the expected values
    if (line[i] != '\0')
    {
        error("Invalid character in ambient lighting definition", NULL);
    }

    // Set the values in the ambient struct
    ambient->intensity = intensity;
    ambient->color.r = r / 255.0;
    ambient->color.g = g / 255.0;
    ambient->color.b = b / 255.0;
}