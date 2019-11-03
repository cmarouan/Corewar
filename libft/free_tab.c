/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 15:58:41 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 18:18:35 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_tab(char ***tab)
{
	int index;

	index = -1;
	if (*tab != NULL)
	{
		while ((*tab)[++index] != NULL)
			ft_strdel(&(*tab)[index]);
		ft_memdel((void **)tab);
	}
}
