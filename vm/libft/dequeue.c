/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequeue.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 10:04:07 by hmney             #+#    #+#             */
/*   Updated: 2019/09/24 10:07:09 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*dequeue(t_queue *queue)
{
	t_list *elem;

	if (empty_queue(queue))
		return (NULL);
	else
	{
		elem = queue->front;
		queue->front = queue->front->next;
		queue->counter--;
	}
	return (elem);
}
