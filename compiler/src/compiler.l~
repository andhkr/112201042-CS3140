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
int 	Lineno;
int     wflag;
#include "include/ast.h"
#include "include/symbtbl_manager.h"
#include "include/stack.h"
#include "y.tab.h"
#include <stdbool.h>
%}

%option noyywrap
digit	[0-9]
letter	[a-zA-Z]

%%
write			{
					yylval.treeNode = create_empty_node("write");
					return WRITE;
				}	
integer			{
					curr_datatype = INT;
					yylval.treeNode = create_empty_node("integer");
					return T_INT;	
				}		

boolean			{;
					curr_datatype = BOOL;
					yylval.treeNode = create_empty_node("boolean");
					return T_BOOL;	
				}

decl		{
					wflag = 1;
					// node* decl = create_empty_node();
					// decl->label = strdup("DECL");
					yylval.treeNode = NULL;
					return DECL;
				}
enddecl			{
					// node* enddecl = create_empty_node();
					// enddecl->label = "ENDDECL";
					yylval.treeNode = NULL;
					wflag = 0;
					return ENDDECL;
				}
begin           {}
end             {}
true           {	yylval.b_var = true;
					return T;
				}
false           {	yylval.b_var = false;
					return F;
				}
if				{
					yylval.treeNode = create_empty_node("if");
					push_stmt(&stm_stack,IF_STMT);
					return IF;
				}
then			{
				}	
else			{
					yylval.treeNode = create_empty_node("else");
					push_stmt(&stm_stack,ELSE_STMT);
					bool val = !(symbltbl->scope_level_truth);
					if(stm_stack.sp >= 2){
						val = val & stm_stack.array[(stm_stack.sp-1)].cond_val;
					}
					stm_stack.array[(stm_stack.sp-1)].cond_val = val;
					stm_stack.cond_val  =  val;
					return ELSE;
				}	
endif				{
				}
for 			{
					yylval.treeNode = create_empty_node("for");
					push_stmt(&stm_stack,FOR_STMT);
					return FOR;
				}		
"=="			{
					yylval.treeNode = create_empty_node("==");
					return EQUALEQUAL;
				}	
"<="			{
					yylval.treeNode = create_empty_node("<=");
					return LESSTHANOREQUAL;
				}
">="			{
					yylval.treeNode = create_empty_node(">=");
					return GREATERTHANOREQUAL;
				}
"!="			{
					yylval.treeNode = create_empty_node("!=");
					return NOTEQUAL;
				}	
AND				{
					yylval.treeNode = create_empty_node("and");
					return LOGICAL_AND;
				}	
OR				{
					yylval.treeNode = create_empty_node("or");
					return LOGICAL_OR;
				}
NOT				{
					yylval.treeNode = create_empty_node("not");
					return LOGICAL_NOT;
				}

break          	{	yylval.treeNode = create_empty_node("break");
					return BREAK_Y;
				}
{digit}+		{ 	
					yylval.var = atoi(yytext);
					return NUM;
				}
{letter}({letter}|{digit})*	{
								if(wflag == 1){
									datavalue v;
									v.integer= 0;
									symbltblentry* entr = add_entry(symbltbl,strdup(yytext),curr_datatype,v);
									yylval.entry = entr;
								}else{
									symbltblentry* entr = get_entry(symbltbl,strdup(yytext));
									yylval.entry = entr;
								}
								return VAR;
							}
[-+*/=()><;,\{\}\[\]\%]     {
						if(*yytext == '{'){
							symbltbl = create_symbtbl(64,hashvalue_of_key,0);
							push_back(&manager,symbltbl);
						}
						else if(stm_stack.sp != 0 && *yytext == '}'){
							pop_stmt(&stm_stack);
							pop_back(&manager);
						}
						return *yytext;
				}			
\n                  {
						;
					}
[ \t]				{
	 					;
					}
.					{
						printf("Some new string which not in grammer\n");
						exit(EXIT_FAILURE);
					}		

%%

