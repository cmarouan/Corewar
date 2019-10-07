/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 15:58:41 by hmney             #+#    #+#             */
/*   Updated: 2019/07/24 15:59:11 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	free_tab(char ***tab)
{
	int index;

	index = 0;
	if (*tab != NULL)
	{
		while ((*tab)[index] != NULL)
		{
			ft_strdel(&(*tab)[index]);
			index++;
		}
		free(*tab);
		*tab = NULL;
	}
	return (0);
}
