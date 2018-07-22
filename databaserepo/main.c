/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwright <mlwright09@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 23:20:20 by mwright           #+#    #+#             */
/*   Updated: 2017/05/05 22:21:32 by mwright          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	clear_stdin(void)
{
	int c;

	c = 0;
	while ((c = getchar()) != '\n')
		;
}

void	read_all(void)
{
	int		r;
	FILE	*f;
	int		res;

	res = 0;
	if (!(f = fopen("db.txt", "r")))
	{
		printf("\e[31mError, this file does not exist");
		exit(1);
	}
	while ((r = fgetc(f)) != EOF)
	{
		printf("%c", r);
		if (r == '}')
		{
			printf("\033[22;35m\nTo continue enter 2, to exit enter 3\n\33[0m");
			scanf("%i", &res);
			clear_stdin();
			if (res == 3)
				exit(0);
			continue;
		}
		if (feof(f))
			break ;
	}
	fclose(f);
}

void	commands(int command)
{
	t_node	*nodes;

	if (command == 2)
		read_all();
	else if (command == 3)
		nodes = query_record("db.txt");
	else if (command == 4)
	{
		nodes = read_db("db.txt");
		nodes = update_record(nodes);
		if (!nodestofile(nodes, "db.txt"))
			exit(0);
	}
	else if (command == 5)
	{
		nodes = read_db("db.txt");
		nodes = delete_record(nodes);
		if (!nodestofile(nodes, "db.txt"))
			exit(0);
	}
	else if (command == 6)
		exit(0);
	else
	{
		printf("\e[31mInvalid selection.\33[0m\n");
		choose_command();
	}
}

void	choose_command(void)
{
	int		command;
	FILE	*f;
	int		id;

	printf("\033[22;35mSelect a command: 1) CREATE 2) READ 3) QUERY 4)"
	"UPDATE 5) DELETE 6) EXIT\n\33[0m");
	printf("Note: '}' and ',' are not allowed characters in this program\n");
	scanf("%i", &command);
	clear_stdin();
	if (command == 1)
	{
		if (!(f = fopen("db.txt", "a+")))
		{
			printf("Error creating file");
			exit(1);
		}
		id = create_label(f);
		fclose(f);
		f = fopen("db.txt", "r+");
		fprintf(f, "%i>", id);
		fclose(f);
	}
	else if (command > 1 || command < 1)
		commands(command);
	return ;
}

int		main(void)
{
	while (1)
		choose_command();
	return (0);
}
