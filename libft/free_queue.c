/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 10:03:35 by hmney             #+#    #+#             */
/*   Updated: 2019/09/24 10:06:01 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_queue(t_queue *queue)
{
	t_list *temp;

	while (!empty_queue(queue))
	{
		temp = dequeue(queue);
		ft_memdel((void **)&temp);
	}
}
