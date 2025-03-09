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
	#include "include/stack.h"
	#include "include/interpreter.h"
	int yylex();
	void yyerror( char* );
	extern FILE* yyin;
	extern int wflag;
	int i;
	#define YYERROR_VERBOSE
%}

%union{
	int var;
	bool b_var;
	node*  treeNode;
	symbltblentry* entry;
}

%token <treeNode> WRITE DECL ENDDECL T_INT T_BOOL
%token <treeNode> IF ELSE
%token <treeNode> LOGICAL_AND LOGICAL_NOT LOGICAL_OR
%token <treeNode> EQUALEQUAL LESSTHANOREQUAL GREATERTHANOREQUAL NOTEQUAL
%token <treeNode> FOR BREAK_Y 
%token <entry> VAR
%token <var> NUM 
%token <b_var> T F
%token <var> THEN ENDIF
%token BEG END
%type <treeNode> expr write_stmt assign_stmt Gdecl_list Gdecl
%type <treeNode> ret_type Gid var_expr str_expr Glist 
%type <treeNode> cond_stmt stmt_list statement control_stmt

%right '='
%left '<' '>'
%left EQUALEQUAL LESSTHANOREQUAL GREATERTHANOREQUAL NOTEQUAL
%left '+' '-'
%left '*' '/'
%left '%'
%left LOGICAL_AND LOGICAL_OR
%left LOGICAL_NOT 


%%

	Prog	:	Gdecl_sec MainBlock
		;
		
	Gdecl_sec:	DECL Gdecl_list ENDDECL{}
		;
	Gdecl_list:              {}
		| 	Gdecl Gdecl_list {}
		;
		
	Gdecl 	:	ret_type Glist ';'  {
										$1->ptr_sibling = $2;
										node* dec = create_empty_node("DECL");
										dec->ptr_children_list = $1;
										graph(dec);										
									}
		;
		
	ret_type:	T_INT   | T_BOOL	{
										$$ = $1;
									}
		;
		
	Glist 	:	Gid       	{$$ = $1;}
		|	Gid ',' Glist 	{ 
								$1->ptr_sibling = $3;
								$$ = $1;
							}
		|	func ',' Glist {}
		;
	
	Gid	:	VAR		{ 
						node* var_node = create_empty_node($1->name);
						var_node->entry = $1;
						$$ = var_node;;
					}
		|	Gid '[' NUM ']'	{
						/*array creation*/
						add_array_to_symbtbl($1,$3);
						node* arr = create_empty_node("array declaration");
						char word[13];
						snprintf(word,sizeof(word),"%d",$3);
						node* right = create_empty_node(word);
						arr->ptr_children_list = $1;
						$1->ptr_sibling = right;
						$$ = arr;
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
	MainBlock : stmt_list {}
		|BEG stmt_list END {}
		;
	stmt_list:	/* NULL */		{$$ = NULL;}
		|	statement stmt_list	{$1->ptr_sibling = $2;
									$$ = $1;
									
								}
		|	error ';' 		{fprintf(stderr,"Error : line no: %d : Syntax Error\n",Lineno);
							exit(EXIT_FAILURE);}
		;

	statement:	assign_stmt  ';' { 
									$$ = $1;
									if(stm_stack.sp == 0){
										graph($1);
									}
								
								}
		|	write_stmt ';'		{
									$$ = $1;
									if(stm_stack.sp == 0){
										graph($1);
									}
								}
		|	cond_stmt 			{
									$$ = $1;
									if(stm_stack.sp == 0){
										graph($1);
									}
								}
		|   control_stmt ';' {$$ = $1;}
		;

	write_stmt:	WRITE '(' expr ')' 	{
										$$ = create_node_ast(FUN_CALL,NULL,$1,$3);
									}
		 | WRITE '(''"' str_expr '"'')'      {;}
		;
	
	assign_stmt:/*NULL*/ {$$=NULL;}
	|var_expr '=' expr  		{ 	
											$$ = create_node_ast(ASSIGN,NULL,$1,$3);	
										}
		;
	cond_stmt:	IF expr THEN stmt_list ENDIF{	
												node* cond = create_empty_node("if_condition");
												node* body = create_empty_node("if_body");
												$1->ptr_children_list = cond;
												cond->ptr_children_list = $2;
												cond->ptr_sibling = body;
												body->ptr_children_list = $4;
												if(stm_stack.sp == 0){
													interprete($1);
												}
												$$ = $1;
										}
		|	IF expr THEN stmt_list ELSE stmt_list ENDIF 	{ 
																node* branch = create_empty_node("branch");
																node* cond = create_empty_node("if_condition");
																node* body = create_empty_node("if_body");
																node* else_body = create_empty_node("else_body");
																branch->ptr_children_list = $1;
																$1->ptr_children_list = cond;
																cond->ptr_children_list = $2;
																cond->ptr_sibling = body;
																body->ptr_children_list = $4;
																$1->ptr_sibling = $5;
																$5->ptr_children_list = else_body;
																else_body->ptr_children_list = $6;
																if(stm_stack.sp == 0){
																	interprete($1);
																}
																$$ = branch;
															}
	    |    FOR '(' assign_stmt  ';'  expr ';'  assign_stmt ')' '{' stmt_list '}'	{ 
																						// $1->ptr_children_list = $3;
																						node* asgn_stmt = create_empty_node("assign_stmt");
																						node* cond_stmt = create_empty_node("condition");
																						node* iterate   = create_empty_node("iterator");
																						node* body      = create_empty_node("body");
																						// $3->asgn_stmt->ptr_children_list = 
																						$1->ptr_children_list = asgn_stmt;
																						asgn_stmt->ptr_children_list = $3;
																						asgn_stmt->ptr_sibling = cond_stmt;
																						cond_stmt->ptr_children_list = $5;
																						cond_stmt->ptr_sibling = iterate;
																						iterate->ptr_children_list = $7;
																						iterate->ptr_sibling = body;
																						body->ptr_children_list = $10;
																						if(stm_stack.sp == 0){
																							interprete($1);
																						}
																						$$ = $1;
		                                                							}
		;
	control_stmt: BREAK_Y     {$$ = $1;}
	;
	expr	:	NUM 		{
								char word[13];
								snprintf(word,sizeof(word),"%d",$1);
								node* num = create_empty_node(word);
								num->type = INT;
								memset(&num->exp_value,0,sizeof(datavalue));
								num->exp_value.integer = $1;
								$$ = num;
							}
		|		T			{ 						  	
								node* True = create_empty_node("true");
								True->type = BOOL;
								memset(&True->exp_value,0,sizeof(datavalue));
								True->exp_value.boolean = $1;
								$$ = True;
							}
		|		F			{ 
								node* False = create_empty_node("false");
								False->type = BOOL;
								memset(&False->exp_value,0,sizeof(datavalue));
								False->exp_value.boolean = $1;
								$$ = False;
							}
		|	'-' expr		{
								$$ = create_node_ast(U_MINUS,NULL,NULL,$2);
							}
		|	var_expr		{$$ = $1;}
		|	'(' expr ')'		{$$ = $2;}

		|	expr '+' expr 		{ 
									$$ = create_node_ast(PLUS,NULL,$1,$3);
								}
		|	expr '-' expr	 	{
									$$ = create_node_ast(SUB,NULL,$1,$3);
		 						}
		|	expr '*' expr 		{
									$$ = create_node_ast(MUL,NULL,$1,$3);
		 						}
		|	expr '/' expr 		{ 	
									$$ = create_node_ast(DIV,NULL,$1,$3);
								}
		|	expr '%' expr 		{   
									$$ = create_node_ast(MODULO,NULL,$1,$3);				
								}
		|	expr '<' expr		{
									$$ = create_node_ast(LESSTHAN,NULL,$1,$3);
		 						}
		|	expr '>' expr		{
									$$ = create_node_ast(GREATERTHAN,NULL,$1,$3);
		 						}
		|	expr GREATERTHANOREQUAL expr{
									$$ = create_node_ast(GREATT_EQUAL,NULL,$1,$3);
		 						}
		|	expr LESSTHANOREQUAL expr	{
									$$ = create_node_ast(LESST_EQUAL,NULL,$1,$3);
		  						}
		|	expr NOTEQUAL expr			{
									$$ = create_node_ast(NOT_EQAUL,NULL,$1,$3);
		 						}	
		|	expr EQUALEQUAL expr	{
										$$ = create_node_ast(EQUAL_EQUAL,NULL,$1,$3);
		 							}
		|	LOGICAL_NOT expr	{
			 							$$ = create_node_ast(Logical_NOT,NULL,$2,NULL);	 			
					}
		|	expr LOGICAL_AND expr	{ 
										$$	= 	create_node_ast(Logical_AND,NULL,$1,$3);	
				}
		|	expr LOGICAL_OR expr	{
										$$	= 	create_node_ast(Logical_OR,NULL,$1,$3);
		}
		;
	str_expr :  VAR {		node* var_node = create_empty_node($1->name);
							var_node->entry = $1;
							update_data(&var_node->exp_value,&$1->value,datasize[$1->type]);
							$$ = var_node;
								}
                  | str_expr VAR   { ;}
                ;
	
	var_expr:	VAR	{			node* var_node = create_empty_node($1->name);
								var_node->entry = $1;
								update_data(&var_node->exp_value,&$1->value,datasize[$1->type]);
								$$ = var_node;
					}
		|	var_expr '[' expr ']'	{
										char* label = "ArrayAccess";
										$1->label = strdup(label);
										node* index = create_empty_node("index");
										if($3->entry == NULL)
										index->exp_value.integer = $3->exp_value.integer;
										index->entry = $3->entry;
										// make_node($1);
										node* left = create_empty_node($1->entry->name);
										$1->ptr_children_list = left;
										left->ptr_sibling = index;
										$1->type = $1->entry->type;
										$$ = $1;
									} 
		;
%%

void yyerror ( char  *s) {
   fprintf (stderr, "%s\n", s);
}

int main(int argc,char** argv){
	symbltbl = create_symbtbl(64,hashvalue_of_key,0);
	init_symbtbl_manager(&manager);
	push_back(&manager,symbltbl);
	init_stmt_stack(&stm_stack);
	wflag = 1;
	yyparse();
	print_symbol_table();
	free_symbol_table_manager(&manager);
	free_graph();
	return 0;
}
