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
	#include <stdbool.h>

	int yylex();
	void yyerror( char* );
	extern FILE* yyin;
	extern int wflag;
	int i;
%}

%union{
	int var;
	bool b_var;
	node*  treeNode;
	symbltblentry* entry;
}

%token <treeNode> WRITE 
%token <treeNode> DECL ENDDECL T_INT T_BOOL
%token <entry> VAR
%token <var> NUM 
%token <b_var> b_NUM
%token <b_var> T F

%type <treeNode> expr write_stmt assign_stmt Gdecl_list Gdecl
%type <treeNode> ret_type Gid var_expr str_expr Glist

%right '='
%left '<' '>'
%left EQUALEQUAL LESSTHANOREQUAL GREATERTHANOREQUAL NOTEQUAL
%left '+' '-'
%left '*' '/'
%left '%'
%left LOGICAL_AND LOGICAL_OR
%left LOGICAL_NOT

%token BEG END
%token IF THEN ELSE ENDIF
%token LOGICAL_AND LOGICAL_NOT LOGICAL_OR
%token EQUALEQUAL LESSTHANOREQUAL GREATERTHANOREQUAL NOTEQUAL
%token FOR 

%%

	Prog	:	Gdecl_sec stmt_list
		;
		
	Gdecl_sec:	DECL Gdecl_list ENDDECL{ 
						$1->left = $2;
						$1->right = $2->right;
						$2->right = NULL;
						print_decl($1);
						}
		;
		
	Gdecl_list:              {$$ = NULL;}
		| 	Gdecl Gdecl_list { 
								node* curr = $1->right;
								node* prev = curr;
								while(curr){
									prev = curr;
									curr = curr->right;
								}
								prev->right = $2;
								$$ = $1;
							}
		;
		
	Gdecl 	:	ret_type Glist ';'  {
										$1->right = $2;
										$$ = $1;
										
									}
		;
		
	ret_type:	T_INT   | T_BOOL	{
										$$ = $1;
									}
		;
		
	Glist 	:	Gid       {$$ = $1;}
		|	Gid ',' Glist { $1->right = $3;
							$$ = $1;
							}
		|	func ',' Glist
		;
	
	Gid	:	VAR		{ 
						$$ = create_node_ast('v',$1,NULL,NULL);
					}
		|	Gid '[' NUM ']'	{
						/*array creation*/
						add_array_to_symbtbl($1,$3);
						$$ = $1;
					}
	func 	:	VAR '(' arg_list ')' 					{ 					}
		;
			
	arg_list:	
		|	arg_list1
		;
		
	arg_list1:	arg_list1 ';' arg
		|	arg
		;
		
	arg 	:	arg_type var_list	
		;
		
	arg_type:	T_INT		 {  }
		;

	var_list:	VAR 		 { }
		|	VAR ',' var_list { 	}
		;		

	stmt_list:	/* NULL */		{  ;}
		|	statement stmt_list	{						}
		|	error ';' 		{fprintf(stderr,"Error : Syntax Error\n");}
		;

	statement:	assign_stmt  ';' { /*print asignment syntax tree*/
									graph($1);
									
								}
		|	write_stmt ';'		 {/*print asignment syntax tree*/
									graph($1);
								}
		|	cond_stmt 			{ }
		;

	write_stmt:	WRITE '(' expr ')' 	{
										$$ = create_node_ast('c',NULL,$1,$3);
									}
		 | WRITE '(''"' str_expr '"'')'      { /*unable to understand*/;}
		;
	
	assign_stmt:	var_expr '=' expr  	{ 	
											$$ = create_node_ast('=',NULL,$1,$3);		
											if($1->type == INTARRAY){
												// printf("%d")
												$1->entry->value.intarr.ptr[$1->entry->value.intarr.index] = $3->exp_value.integer;
											}	
											// printf("RAdha5\n");
										}
		;
	cond_stmt:	IF expr THEN stmt_list ENDIF 	{ 						}
		|	IF expr THEN stmt_list ELSE stmt_list ENDIF 	{ 						}
	        |    FOR '(' assign_stmt  ';'  expr ';'  assign_stmt ')' '{' stmt_list '}'                                             {                                                 }
		;

	expr	:	NUM 		{
								node* num = create_node_ast('d',NULL,NULL,NULL);
								num->type = INT;
								memset(&num->exp_value,0,sizeof(datavalue));
								num->exp_value.integer = $1;
								char word[13];
								snprintf(word,sizeof(word),"%d",$1);
								num->statement = strdup(word); 
								$$ = num;
							}
		|   	b_NUM 		{
								node* b_num = create_node_ast('d',NULL,NULL,NULL);
								b_num->type = BOOL;
								memset(&b_num->exp_value,0,sizeof(datavalue));
								b_num->exp_value.boolean = $1;
								char word[13];
								snprintf(word,sizeof(word),"%d",$1);
								b_num->statement = strdup(word); 
								$$ = b_num;
							}
		|	T			{ 						  	}
		|	F			{ 	}
		|	'-' expr			{
								$$ = create_node_ast('u',NULL,NULL,$2);
							}
		|	var_expr		{$$ = $1;}
		|	'(' expr ')'		{$$ = $2;}

		|	expr '+' expr 		{ 
									$$ = create_node_ast('+',NULL,$1,$3);
								}
		|	expr '-' expr	 	{
									$$ = create_node_ast('-',NULL,$1,$3);
		 						}
		|	expr '*' expr 		{
									$$ = create_node_ast('*',NULL,$1,$3);
		 						}
		|	expr '/' expr 		{ 	
									$$ = create_node_ast('/',NULL,$1,$3);
								}
		|	expr '%' expr 		{ 						}
		|	expr '<' expr		{ 						}
		|	expr '>' expr		{ 						}
		|	expr GREATERTHANOREQUAL expr				{ 						}
		|	expr LESSTHANOREQUAL expr	{  						}
		|	expr NOTEQUAL expr			{ 						}
		|	expr EQUALEQUAL expr	{ 						}
		|	LOGICAL_NOT expr	{ 						}
		|	expr LOGICAL_AND expr	{ 						}
		|	expr LOGICAL_OR expr	{}
		;
	str_expr :  VAR {			$$ = create_node_ast('v',$1,NULL,NULL);
								
								}
                  | str_expr VAR   { ;}
                ;
	
	var_expr:	VAR	{			 $$ = create_node_ast('v',$1,NULL,NULL);}
		|	var_expr '[' expr ']'	{
										$1->statement = "Array";
										$1->type = INTARRAY;
										$1->entry->value.intarr.index = $3->exp_value.integer;
										$$ = $1;
										// printf("RAdha\n");
									} 
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
	free_symbol_table_manager(&manager);
	free_graph();
	return 0;
}
