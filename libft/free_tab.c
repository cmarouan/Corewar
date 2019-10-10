/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 15:58:41 by hmney             #+#    #+#             */
/*   Updated: 2019/10/08 16:11:33 by hmney            ###   ########.fr       */
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
