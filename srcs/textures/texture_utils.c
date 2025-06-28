/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:12:16 by leaugust          #+#    #+#             */
/*   Updated: 2025/06/28 13:41:24 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	handle_ceiling(t_texpath *texpath, char *line)
{
	char	*trimmed;

	if (texpath->ceiling)
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
	if (parse_rgb(trimmed, &texpath->ceiling_rgb))
	{
		free(trimmed);
		return (1);
	}
	texpath->ceiling = trimmed;
	return (0);
}

int	handle_floor(t_texpath *texpath, char *line)
{
	char	*trimmed;

	if (texpath->floor)
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
	if (parse_rgb(trimmed, &texpath->floor_rgb))
	{
		free(trimmed);
		return (1);
	}
	texpath->floor = trimmed;
	return (0);
}

int	destroy_texpath(t_texpath *texpath)
{
	if (texpath == NULL)
		return (perror("texpath is NULL"), 1);
	if (texpath->no)
		free(texpath->no);
	if (texpath->so)
		free(texpath->so);
	if (texpath->we)
		free(texpath->we);
	if (texpath->ea)
		free(texpath->ea);
	if (texpath->floor)
		free(texpath->floor);
	if (texpath->ceiling)
		free(texpath->ceiling);
	return (0);
}

int	check_textures(t_texpath *texpath)
{
	if (!texpath->no || !texpath->so || !texpath->we || !texpath->ea
		|| !texpath->floor || !texpath->ceiling)
		return (perror("Missing texture paths"), 1);
	if (check_exist_textures(texpath))
		return (1);
	if (check_xpm_file(texpath->no) || check_xpm_file(texpath->so)
		|| check_xpm_file(texpath->we) || check_xpm_file(texpath->ea))
		return (1);
	return (0);
}
