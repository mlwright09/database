/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_record.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwright <mlwright09@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 22:43:36 by mwright           #+#    #+#             */
/*   Updated: 2017/05/05 23:18:46 by mwright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	free_dataitem(t_data_item **dataitem)
{
	t_data_item		*d;
	t_data_item		*next;

	d = *dataitem;
	while (d)
	{
		next = d->next;
		free(d->key);
		free(d->value);
		free(d);
		d = next;
	}
	*dataitem = NULL;
}

void	delete_node(t_node **del_node)
{
	t_node	*d;
	t_node	*n;
	t_node	*p;
	int		i;

	d = *del_node;
	n = d->next;
	p = d->prev;
	if (n)
		n->prev = p;
	if (p)
		p->next = n;
	d->id = 0;
	free(d->label);
	i = -1;
	while (d->tags[++i])
		free(d->tags[i]);
	free(d->tags);
	d->next = NULL;
	d->prev = NULL;
	free_dataitem(&d->details);
	free(d->details);
	*del_node = d;
}

int		delete_confirmprompt(void)
{
	char	confirm;

	confirm = 42;
	while (confirm != 'y' && confirm != 'n')
	{
		ft_putendl("Confirm that you want to delete this node? (y/n)");
		scanf(" %c", &confirm);
		clear_stdin_buff();
	}
	if (confirm == 'y')
		return (1);
	else
		return (0);
}

int		delete_idselection(t_node *n, t_node **del)
{
	t_node	*del_node;
	int		node_id;

	del_node = NULL;
	while (!del_node)
	{
		ft_putstr("\x1b[36mPlease enter the index number of the node ");
		ft_putendl("you would like to delete (integer only):\033[0m");
		scanf("%i", &node_id);
		clear_stdin_buff();
		if (!(del_node = find_node_by_id(n, node_id)))
		{
			del_node = NULL;
			ft_putendl("Please check the id number entered.");
		}
	}
	*del = del_node;
	return (node_id);
}

t_node	*delete_record(t_node *nodes)
{
	t_node	*n;
	t_node	*del_node;
	int		node_id;
	int		confirm;

	n = nodes;
	if (!n)
	{
		ft_putstr("Database is currently empty.  Try CREATE first.");
		return (NULL);
	}
	del_node = NULL;
	node_id = delete_idselection(n, &del_node);
	print_node(del_node, 0);
	confirm = delete_confirmprompt();
	if (confirm)
	{
		delete_node(&del_node);
		ft_putstr("\x1b[36mEntry with ID ");
		ft_putnbr(node_id);
		ft_putendl(" deleted.\033[0m");
	}
	return (nodes);
}
