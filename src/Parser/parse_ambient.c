/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pare_ambient.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:41:08 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/05 08:41:54 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void parse_ambient(char *line, t_amblight *ambient)
{
    int i = 1; // Start after 'A'
    float intensity;
    int r, g, b;

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    // Check for invalid characters in intensity
    if (!ft_isdigit(line[i]) && line[i] != '-' && line[i] != '+')
    {
        error("Invalid character in ambient lighting intensity", NULL);
    }
    // Parse intensity
    intensity = ft_atof(&line[i]);
    if (intensity < 0.0 || intensity > 1.0)
    {
        error("Ambient lighting intensity out of range [0.0, 1.0]", NULL);
    }
    printf("Parsed intensity: %f\n", intensity);

    // Move index to next part (skipping the intensity part)
    while (line[i] && (line[i] != ' ' && line[i] != '\t'))
        i++;

    // Skip whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Check for invalid characters in red value
    if (!ft_isdigit(line[i]) && line[i] != '-' && line[i] != '+')
    {
        error("Invalid character in ambient lighting red value", NULL);
    }
    // Parse RGB values
    r = ft_atoi(&line[i]);
    if (r < 0 || r > 255)
    {
        error("Ambient lighting red value out of range [0, 255]", NULL);
    }
    printf("Parsed red: %d\n", r);
    while (line[i] && line[i] != ',')
        i++;
    if (line[i] == ',')
        i++;
    // Check for invalid characters in green value
    if (!ft_isdigit(line[i]) && line[i] != '-' && line[i] != '+')
    {
        error("Invalid character in ambient lighting green value", NULL);
    }
    g = ft_atoi(&line[i]);
    if (g < 0 || g > 255)
    {
        error("Ambient lighting green value out of range [0, 255]", NULL);
    }
    printf("Parsed green: %d\n", g);
    while (line[i] && line[i] != ',')
        i++;
    if (line[i] == ',')
        i++;

    // Check for invalid characters in blue value
    if (!ft_isdigit(line[i]) && line[i] != '-' && line[i] != '+')
    {
        error("Invalid character in ambient lighting blue value", NULL);
    }

    b = ft_atoi(&line[i]);
    if (b < 0 || b > 255)
    {
        error("Ambient lighting blue value out of range [0, 255]", NULL);
    }
    printf("Parsed blue: %d\n", b);

    // Check for unexpected characters after parsing
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    if (line[i] && !ft_isdigit(line[i]) && line[i] != '\0')
    {
        error("Unexpected character in ambient lighting definition", NULL);
    }

    // Set the values in the ambient struct
    ambient->intensity = intensity;
    ambient->color.r = r / 255.0;
    ambient->color.g = g / 255.0;
    ambient->color.b = b / 255.0;
}