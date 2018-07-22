/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwright <mlwright09@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 13:39:14 by mwright           #+#    #+#             */
/*   Updated: 2017/05/05 21:53:38 by mwright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DB_H
# define FT_DB_H
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include "libft/libft.h"

typedef struct			s_data_item
{
	char				*key;
	char				*value;
	struct s_data_item	*next;
	struct s_data_item	*prev;
}						t_data_item;
typedef struct			s_node
{
	int					id;
	char				*label;
	t_data_item			*details;
	char				**tags;
	struct s_node		*next;
	struct s_node		*prev;
}						t_node;

void					clear_stdin_buff(void);
void					clear_stdin(void);

t_node					*find_node_by_id(t_node *nodes, int id);
void					delete_node(t_node **del_node);
void					free_dataitem(t_data_item **dataitem);

void					update_detailfound(t_data_item **dataitem, int i);
void					update_nodedetail(t_data_item **dataitem, int i);
int						update_confirmprompt(char *type);
int						*update_detailsinput(int *strcount, int detailcount);
void					update_details(t_node **node);

int						delete_confirmprompt(void);
int						delete_idselection(t_node *n, t_node **del);

int						main(void);
void					choose_command();
void					commands(int command);
void					read_all(void);
int						create_label(FILE *f);
void					detail_entry(int detail_lines, FILE *f);
int						end_id(FILE *f);
void					create_tag(FILE *f);
void					tag_it(int res, FILE *f);

int						arrlen(char **arr);
int						dataitem_count(t_data_item *dataitem);
void					print_node(t_node *node, int detail_index);
t_node					*find_node_by_id(t_node *nodes, int id);
int						node_count(t_node *nodes);
void					add_node(t_node **head, t_node *new);
t_node					*init_node(char *data);
t_node					*read_db(char *fname);
t_node					*query_record(char	*fname);
int						nodestofile(t_node *nodes, char *fname);
t_node					*update_record(t_node *nodes);
t_node					*delete_record(t_node *nodes);
#endif
