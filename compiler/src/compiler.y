/*
 *   This file is part of SIL Compiler.
 *
 *  SIL Compiler is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SIL Compiler is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with SIL Compiler.  If not, see <http://www.gnu.org/licenses/>.
 */

%{	
	#include <stdio.h>
	#include "include/ast.h"
	#include "include/symbtbl_manager.h"
	#include <assert.h>
	int yylex();
	void yyerror( char* );
	extern FILE* yyin;
	extern int wflag;
%}

%union{
	int var;
	node*  treeNode;
	symbltblentry* entry;
}

%token <treeNode> WRITE
%token <treeNode> DECL ENDDECL T_INT VAR
%token <var> NUM

%type <treeNode> expr write_stmt assign_stmt Gdecl_list Gdecl
%type <treeNode> ret_type Gid var_expr str_expr Glist

%right '='
%left '+' '-'
%left '*' '/'

%%

	Prog	:	Gdecl_sec stmt_list
		;
		
	Gdecl_sec:	DECL Gdecl_list ENDDECL{ 
						$1->left = $2;
						$1->right = $2->right;
						$2->right = NULL;
						// // print_ast($$);/*declarative syntax tree will be printed*/
						// printf("4 %s ",$1->value.statement);
						print_ast($1);
						printf("\n");
						}
		;
		
	Gdecl_list: 
		| 	Gdecl Gdecl_list { 
		$$ = $1;
		}
		;
		
	Gdecl 	:	ret_type Glist ';'  {
										$1->right = $2;
										$$ = $1;
										
									}
		;
		
	ret_type:	T_INT		{
								$$ = $1;
							}
		;
		
	Glist 	:	Gid       {$$ = $1;}
		|	Gid ',' Glist { $1->right = $3;
							$$ = $1;
							}
		;
	
	Gid	:	VAR		{ 
						$$ = $1;
					}
		|	Gid '[' NUM ']'	{}

		;		

	stmt_list:	/* NULL */		{  ;}
		|	statement stmt_list	{						}
		|	error ';' 		{fprintf(stderr,"Error : Syntax Error\n");}
		;

	statement:	assign_stmt  ';' { print_ast($1); printf("\n")/*print asignment syntax tree*/;}
		|	write_stmt ';'		 {/*print asignment syntax tree*/
									print_ast($1);printf("\n");}
		;

	write_stmt:	WRITE '(' expr ')' 	{
										nodevalue v1;
										v1.statement = "CALL";
										node* call = create_node_ast(STATEMENT,v1,$3->exp_value);
										call->right = $3;
										call->left  = $1;
										$$=call;
	
									}
		 | WRITE '(''"' str_expr '"'')'      { /*unable to understand*/;}
		;
	
	assign_stmt:	var_expr '=' expr  	{ 	
											nodevalue v1;
											v1.op = '=';				
											node* asgn = create_node_ast(OP,v1,0);
											$1->value.entry->value.integer = $3->exp_value;
											$1->exp_value = $3->exp_value;
											asgn->left = $1;
											asgn->right = $3;
											asgn->exp_value = $3->exp_value;
											$$ = asgn;
										}
		;

	expr	:	NUM 		{
								nodevalue v;
								v.num = $1;
								$$ = create_node_ast(INT,v,$1);
							}
		|	'-' NUM			{
								nodevalue v1;
								v1.op = '-';
								nodevalue v2;
								v2.num = -$2;
								node* neg = create_node_ast(OP,v1,-$2);
								neg->right = create_node_ast(INT,v2,-$2);
								$$ = neg;
							}
		|	var_expr		{$$ = $1;}
		|	'(' expr ')'		{$$ = $2;}

		|	expr '+' expr 		{ 
									nodevalue v1;
									v1.op = '+';
									node* op = create_node_ast(OP,v1,($1->exp_value + $3->exp_value));
									op->left = $1;
									op->right = $3;
									$$ = op;
								}
		|	expr '-' expr	 	{
									nodevalue v1;
									v1.op = '-';
									node* op = create_node_ast(OP,v1,($1->exp_value - $3->exp_value));
									op->left = $1;
									op->right = $3;
									$$ = op;
		 						}
		|	expr '*' expr 		{
									nodevalue v1;
									v1.op = '*';
									node* op = create_node_ast(OP,v1,($1->exp_value * $3->exp_value));
									op->left = $1;
									op->right = $3;
									$$ = op;
		 						}
		|	expr '/' expr 		{ 	
									assert($3->exp_value != 0);
									nodevalue v1;
									v1.op = '/';
									node* op = create_node_ast(OP,v1,($1->exp_value / $3->exp_value));
									op->left = $1;
									op->right = $3;
									$$ = op;
								}

		;
	str_expr :  VAR {			$$ = $1;
								
								}
                  | str_expr VAR   { ;}
                ;
	
	var_expr:	VAR	{			$$ = $1;}
		|	var_expr '[' expr ']'	{            ;                                    }
		;
%%

void yyerror ( char  *s) {
   fprintf (stderr, "%s\n", s);
}

int main(int argc,char** argv){
	symbtbl = create_symbtbl(64,hashvalue_of_key,0);
	init_symbtbl_manager(&manager);
	push_back(&manager,symbtbl);
	wflag = 1;
	yyparse();
	print_symbol_table();
	return 0;
}
