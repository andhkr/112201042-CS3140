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
%}

%option noyywrap
digit	[0-9]
letter	[a-zA-Z]

%%
write			{
					nodevalue v2;
					v2.statement = "write";
					node* write = create_node_ast(STATEMENT,v2,0);
					yylval.treeNode = write;
					return WRITE;
				}	
integer			{
					nodevalue v;
					v.statement = "integer";
					yylval.treeNode = create_node_ast(STATEMENT,v,0);
					return T_INT;	
				}		
begindecl		{
					wflag = 1;
					nodevalue v;
					v.statement = "DECL";
					yylval.treeNode = create_node_ast(STATEMENT,v,0);
					return DECL;
				}
enddecl			{
					nodevalue v;
					v.statement = "";
					yylval.treeNode = create_node_ast(STATEMENT,v,0);
					wflag = 0;
					return ENDDECL;
				}

{digit}+		{ 	
					yylval.var = atoi(yytext);
					return NUM;
				}

{letter}({letter}|{digit})*	{
								if(wflag == 1){
									datavalue v;
									v.integer= 0;
									symbltblentry* entr = add_entry(manager.array[0],strdup(yytext),INT,v);
									nodevalue v1;
						            v1.entry = entr;
									yylval.treeNode = create_node_ast(ENTRY,v1,0);
								}else{
									symbltblentry* entr = get_entry(manager.array[0],strdup(yytext),INT);
									nodevalue v1;
						            v1.entry = entr;
									yylval.treeNode = create_node_ast(ENTRY,v1,entr->value.integer);
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

