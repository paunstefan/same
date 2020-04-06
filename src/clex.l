O   [0-7]
D   [0-9]
NZ  [1-9]
L   [a-zA-Z_]
A   [a-zA-Z_0-9]
H   [a-fA-F0-9]
HP  (0[xX])
E   ([Ee][+-]?{D}+)
P   ([Pp][+-]?{D}+)
FS  (f|F|l|L)
IS  (((u|U)(l|L|ll|LL)?)|((l|L|ll|LL)(u|U)?))
CP  (u|U|L)
SP  (u8|u|U|L)
ES  (\\(['"\?\\abfnrtv]|[0-7]{1,3}|x[a-fA-F0-9]+))
WS  [ \t\v\n\f]

%{
#include <stdio.h>
#include <string.h>
#include "util.h"

void comment();
%}

%option yylineno
%option nounput

%%
"/*"					{ comment(); }
"//".*					{ /* consume //-comment */ }

"auto"					{  }
"break"					{  }
"case"					{  }
"char"					{  }
"const"					{  }
"continue"				{  }
"default"				{  }
"do"					{  }
"double"				{  }
"else"					{  }
"enum"					{  }
"extern"				{  }
"float"					{  }
"for"					{  }
"goto"					{  }
"if"					{  }
"inline"				{  }
"int"					{  }
"long"					{  }
"register"				{  }
"restrict"				{  }
"return"				{  }
"short"					{  }
"signed"				{  }
"sizeof"				{  }
"static"				{  }
"struct"				{  }
"switch"				{  }
"typedef"				{  }
"union"					{  }
"unsigned"				{  }
"void"					{  }
"volatile"				{  }
"while"					{  }
"_Alignas"				{  }
"_Alignof"				{  }
"_Atomic"				{  }
"_Bool"					{  }
"_Complex"				{  }
"_Generic"				{  }
"_Imaginary"			{  }
"_Noreturn"				{  }
"_Static_assert"		{  }
"_Thread_local"			{  }
"__func__"				{  }

{L}{A}*					{ process_word(yytext); }

{HP}{H}+{IS}?				{  }
{NZ}{D}*{IS}?				{  }
"0"{O}*{IS}?				{  }
{CP}?"'"([^'\\\n]|{ES})+"'"		{  }

{D}+{E}{FS}?				{  }
{D}*"."{D}+{E}?{FS}?			{  }
{D}+"."{E}?{FS}?			{  }
{HP}{H}+{P}{FS}?			{  }
{HP}{H}*"."{H}+{P}{FS}?			{  }
{HP}{H}+"."{P}{FS}?			{  }

({SP}?\"([^"\\\n]|{ES})*\"{WS}*)+	{  }
(<([^<\\\n]|{ES})*>{WS}*)+	{  }

"..."					{  }
">>="					{  }
"<<="					{  }
"+="					{  }
"-="					{  }
"*="					{  }
"/="					{  }
"%="					{  }
"&="					{  }
"^="					{  }
"|="					{  }
">>"					{  }
"<<"					{  }
"++"					{  }
"--"					{  }
"->"					{  }
"&&"					{  }
"||"					{  }
"<="					{  }
">="					{  }
"=="					{  }
"!="					{  }
";"					{  }
("{"|"<%")				{  }
("}"|"%>")				{  }
","					{  }
":"					{  }
"="					{  }
"("					{  }
")"					{  }
("["|"<:")				{  }
("]"|":>")				{  }
"."					{  }
"&"					{  }
"!"					{  }
"~"					{  }
"-"					{  }
"+"					{  }
"*"					{  }
"/"					{  }
"%"					{  }
"<"					{  }
">"					{  }
"^"					{  }
"|"					{  }
"?"					{  }
"#define"			{  }
"#undef"			{  }
"#if"				{  }
"#endif"			{  }
"#else"				{  }
"#elif"				{  }
"#include"			{  }
"#ifdef"			{  }
"#ifndef"			{  }
"#error"			{  }
"#pragma"			{  }

{WS}+					{ /* whitespace separates tokens */ }
.					{ /* discard bad characters */ }

%%

int yywrap()		/* called at end of input */
{
	return 1;	/* terminate now */
}

void comment()
{
	int c;

	while ((c = input()) != 0) {
		if (c == '*') {
			while ((c = input()) == '*') ;
			if (c == '/') return;
			if (c == 0) break;
		}
	}
	printf("unterminated comment\n");

}