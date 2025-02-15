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
#include "y.tab.h"
#include <stdbool.h>
%}

%option noyywrap
digit	[0-9]
letter	[a-zA-Z]

%%
write			{
					node* write = create_node_ast('d',NULL,NULL,NULL);
					write->statement = "write";
					yylval.treeNode = write;
					return WRITE;
				}	
integer			{;
					curr_datatype = INT;
					node* integer = create_node_ast('d',NULL,NULL,NULL);
					integer->statement = "integer";
					yylval.treeNode = integer;
					return T_INT;	
				}		

bool			{;
					curr_datatype = BOOL;
					node* boolean = create_node_ast('d',NULL,NULL,NULL);
					boolean->statement = "boolean";
					yylval.treeNode = boolean;
					return T_BOOL;	
				}

begindecl		{
					wflag = 1;
					node* decl = create_node_ast('d',NULL,NULL,NULL);
					decl->statement = "DECL";
					yylval.treeNode = decl;
					return DECL;
				}
enddecl			{
					node* enddecl = create_node_ast('d',NULL,NULL,NULL);
					enddecl->statement = "ENDDECL";
					yylval.treeNode = enddecl;
					wflag = 0;
					return ENDDECL;
				}

{digit}+		{ 	
					yylval.var = atoi(yytext);
					return NUM;
				}

True           {	yylval.b_var = 1;
					return b_NUM;
				}
False           {	yylval.b_var = 0;
					return b_NUM;
				}
{letter}({letter}|{digit})*	{
								if(wflag == 1){
									datavalue v;
									v.integer= 0;
									symbltblentry* entr = add_entry(manager.array[0],strdup(yytext),curr_datatype,v);
									yylval.entry = entr;
								}else{
									symbltblentry* entr = get_entry(manager.array[0],strdup(yytext));
									yylval.entry = entr;
								}
								return VAR;
							}
[-+*/=();,]         {
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

