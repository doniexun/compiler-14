#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include "util.h"

#define BUFF_SIZE	(100)


struct var {
	char*			var;
	int			value;
};

enum op {
	PLUS, MIN, MUL, DIV
}

struct op {
	enum op 		op_type;
	struct expr		left;
	struct expr		right;
};

enum expr_type {
	OP, CONST, VAR
};

struct expr {
	enum expr_type		expr_type;
	union {
		struct op 	op;	
		struct var	var;
		int		val;	
	} this;
};

struct assignment {
	char 			var;
	struct expr		expr;
};


struct program {
	struct list*	stmt;
} program;


void parse_name(char** pg)
{
	struct var	var;
	int		i;
	char*		name;
	int		buff[10];

	for (i = 0; *pg != ' '; i+=1) {
		buff[i] = *pg;
		pg += 1;
	}

	return name;
}

void parse_stmt(char* pg)
{
	char* name;
	if (isalpha(*pg) || '_') {
		name = parse_name(&pg);
	}
	

	switch (*pg) {
		case '+':
			eval_expr(expr + 1);
		case '-':
			eval_expr(expr + 1);
		case '*':
			eval_expr(expr + 1);
		case '/':
			eval_expr(expr + 1);
		case '(':
		case ')':
		default:
			eval_expr(expr + 1);
	}
}

int main(int args, char** argv)
{
	FILE*	fp;
	char	buff[BUFF_SIZE];
	char*	program;
	char*	old_program;
	size_t	amount;
	size_t	old_amount;

	if (args < 2)
		error("Too few arguements");

	fp = fopen(argv[1], "r");

	if (NULL == fp)	
		perror("svm error ");

	/* Read the file into heap memory */

	amount = old_amount = 0;
	program = old_program =  NULL;

	do {
		old_amount = amount;
		amount += fread(buff, 1, BUFF_SIZE, fp);
		program = realloc(old_program, amount);
		if (NULL == program)
			goto CLEAN;
		old_program = program;
		memcpy(&program[old_amount], buff, amount);
	} while (BUFF_SIZE == amount);

	//parse(program, amount, amount);

	CLEAN:
	free(old_program);
	fclose(fp);

	return 0;
}
