// NEEDS HEADER

#include "ft_db.h"

int		validate_query(char *q, char *q_cmds[], int *index)
{
//	char	q_cmds[11];
	int		i;

/*	q_cmds[0] = "SELECT ";
	q_cmds[1] = "UPDATE ";
	q_cmds[2] = "DELETE ";
	q_cmds[3] = "INSERT INTO ";
	q_cmds[4] = "CREATE DATABASE ";
	q_cmds[5] = "ALTER DATABASE ";
	q_cmds[6] = "CREATE TABLE ";
	q_cmds[7] = "ALTER TABLE ";
	q_cmds[8] = "DROP TABLE ";
	q_cmds[9] = "CREATE INDEX ";
	q_cmds[10] = "DROP INDEX ";
	q_cmds[11] = NULL;*/
	i = 0;
	while (q_cmds[i])
	{
		if (strncmp(q, q_cmds[i], strlen(q_cmds[i])))
		{
			*index = i;
			return (1);
		}
		i++;
	}
	return (0);
}
