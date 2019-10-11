/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 15:58:41 by hmney             #+#    #+#             */
/*   Updated: 2019/10/11 18:22:20 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		free_tab(char ***tab)
{
	int index;

	index = -1;
	if (*tab != NULL)
	{
		while ((*tab)[++index] != NULL)
			ft_strdel(&(*tab)[index]);
		ft_memdel((void **)tab);
	}
	return (1);
}
