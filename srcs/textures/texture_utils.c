/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:12:16 by leaugust          #+#    #+#             */
/*   Updated: 2025/06/26 22:19:38 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	handle_ceiling(t_textures *textures, char *line)
{
	char	*trimmed;

	if (textures->ceiling)
	{
		perror("Duplicate C");
		return (1);
	}
	trimmed = ft_strtrim(line + 1, " \t\n");
	if (!trimmed)
	{
		perror("Invalid ceiling color format");
		return (1);
	}
	if (parse_rgb(trimmed, &textures->ceiling_rgb))
	{
		free(trimmed);
		return (1);
	}
	textures->ceiling = trimmed;
	return (0);
}

int	handle_floor(t_textures *textures, char *line)
{
	char	*trimmed;

	if (textures->floor)
	{
		perror("Duplicate F");
		return (1);
	}
	trimmed = ft_strtrim(line + 1, " \t\n");
	if (!trimmed)
	{
		perror("Invalid floor color format");
		return (1);
	}
	if (parse_rgb(trimmed, &textures->floor_rgb))
	{
		free(trimmed);
		return (1);
	}
	textures->floor = trimmed;
	return (0);
}

int	destroy_textures(t_textures *textures)
{
	if (textures == NULL)
		return (perror("textures is NULL"), 1);
	if (textures->no)
		free(textures->no);
	if (textures->so)
		free(textures->so);
	if (textures->we)
		free(textures->we);
	if (textures->ea)
		free(textures->ea);
	if (textures->floor)
		free(textures->floor);
	if (textures->ceiling)
		free(textures->ceiling);
	free(textures);
	return (0);
}

/* Mettre en commentaire check_exist_textures
	+ check_xpm si on veut tester code*/

int	check_textures(t_textures *textures)
{
	if (!textures->no || !textures->so || !textures->we || !textures->ea
		|| !textures->floor || !textures->ceiling)
		return (perror("Missing texture paths"), 1);
	// if (check_exist_textures(textures))
	// 	return (1);
	// if (check_xpm_file(textures->no) || check_xpm_file(textures->so)
	// 	|| check_xpm_file(textures->we) || check_xpm_file(textures->ea))
	// 	return (1);
	return (0);
}
