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
	#include <string.h>
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
%token <treeNode> DECL ENDDECL T_INT
%token <entry> VAR
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
						print_decl($1);
						printf("\n");
						printf("========================================================================================\n");
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
						$$ = create_node_ast($1->name,$1->value.integer,$1);
					}
		|	Gid '[' NUM ']'	{}

		;		

	stmt_list:	/* NULL */		{  ;}
		|	statement stmt_list	{						}
		|	error ';' 		{fprintf(stderr,"Error : Syntax Error\n");}
		;

	statement:	assign_stmt  ';' { /*print asignment syntax tree*/
									printf("AST:\n");
									printtree($1); printf("\n");
									printf("Preorder of AST:\n");
									print_ast($1); printf("\n\n");
									printf("========================================================================================\n");
									
								}
		|	write_stmt ';'		 {/*print asignment syntax tree*/
									printf("AST:\n");
									printtree($1); printf("\n");
									printf("Preorder of AST:\n");
									print_ast($1); printf("\n\n");
									printf("========================================================================================\n");
									
								}
		;

	write_stmt:	WRITE '(' expr ')' 	{
										node* call = create_node_ast("CALL",$3->exp_value,NULL);
										call->right = $3;
										call->left  = $1;
										$$=call;
	
									}
		 | WRITE '(''"' str_expr '"'')'      { /*unable to understand*/;}
		;
	
	assign_stmt:	var_expr '=' expr  	{ 				
											node* asgn = create_node_ast("ASSIGN",0,NULL);
											$1->entry->value.integer = $3->exp_value;
											asgn->left = $1;
											asgn->right = $3;
											asgn->exp_value = $3->exp_value;
											$$ = asgn;
										}
		;

	expr	:	NUM 		{
								$$ = create_node_ast("NUM",$1,NULL);
							}
		|	'-' NUM			{
								node* neg = create_node_ast("UNARYMINUS",-$2,NULL);
								neg->right = create_node_ast("NUM",-$2,NULL);
								$$ = neg;
							}
		|	var_expr		{$$ = $1;}
		|	'(' expr ')'		{$$ = $2;}

		|	expr '+' expr 		{ 
									node* op = create_node_ast("PLUS",($1->exp_value + $3->exp_value),NULL);
									op->left = $1;
									op->right = $3;
									$$ = op;
								}
		|	expr '-' expr	 	{
									node* op = create_node_ast("SUB",($1->exp_value - $3->exp_value),NULL);
									op->left = $1;
									op->right = $3;
									$$ = op;
		 						}
		|	expr '*' expr 		{
									node* op = create_node_ast("MUL",($1->exp_value * $3->exp_value),NULL);
									op->left = $1;
									op->right = $3;
									$$ = op;
		 						}
		|	expr '/' expr 		{ 	
									assert($3->exp_value != 0);
									node* op = create_node_ast("DIV",($1->exp_value / $3->exp_value),NULL);
									op->left = $1;
									op->right = $3;
									$$ = op;
								}

		;
	str_expr :  VAR {			$$ = create_node_ast($1->name,$1->value.integer,$1);
								
								}
                  | str_expr VAR   { ;}
                ;
	
	var_expr:	VAR	{			$$ = create_node_ast($1->name,$1->value.integer,$1);}
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
