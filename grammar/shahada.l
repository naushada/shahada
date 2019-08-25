%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "shahada.tab.h"								
#include "shahada.h"

extern int yyerror(yyscan_t yyscanner, const char *s);

int yywrap(yyscan_t yyscanner) 
{
  return 1;
}

%}

%option reentrant
%option bison-bridge
%option debug
%option warn
%option header-file="parser/shahada.yy.h"
%option outfile="parser/shahada.yy.c"
 /*! This is to remove the warning message*/
%option nounput
%option noinput


 /*Exclusive State for HTTP Parsing State Matching*/
%x MIME_PARAM_ST MIME_VALUE_ST 
%x HTTP_BODY_ST REASON_PHRASE_ST HTTP_CHUNKED_BOBY_ST
%x HTTP_REQ_ST HTTP_RSP_ST QS_PARAM_ST QS_VALUE_ST
%x HTTP_EXT_CHUNK_NAME_ST HTTP_EXT_CHUNK_VALUE_ST

DIGIT                [0-9]
INTEGER              -?(0|[1-9]{DIGIT}*)
NUMBER               {INTEGER}\.{DIGIT}+
ALPHA                [a-zA-Z]
ALPHANUM             [a-zA-Z0-9_\.\-]
HEX                  [0-9a-fA-F]
CRLF                 (\r\n)
SPACE                [ \t]
EQ                   (=)
PROTOCOL             (HTTP)\/{DIGIT}\.{DIGIT} 
METHOD               (OPTIONS|GET|HEAD|POST|PUT|DELETE|TRACE|CONNECT)

URI                  \/{ALPHANUM}*

 /*Delimiters*/
WHAT                 (\?)
AMPERSAND            (&)
COLON                (:)
BODY_START           (\r\n\r\n\r\n|\r\n\r\n)

 /*HTTP Header's Parameters field-name: field-value*/    
MIME_PARAM           {ALPHANUM}+
MIME_VALUE           [a-zA-Z0-9\.\/_\-\'\"; \*=;,+]+ 

 /*Query-string parameters of form field-name=field-value*/
QS_PARAM             {ALPHANUM}+
QS_VALUE             {ALPHANUM}+

 /*Reason Phrase*/
STATUS_STR           [a-zA-Z\- \"\']+
STATUS_CODE          {DIGIT}{3}
 /*The Printable ASCII Character.*/
HTTP_BODY            [\x20-\x7F]+
CHUNK_LENGTH         [1-9a-fA-F][0-9a-fA-F]+
ZERO                 (0)
CHUNK_EXT            (;)
CHUNK_EXT_NAME       [1-9a-zA-Z\.\-\"\'\!\#\$\%\&\*\^+_\`\~]+
CHUNK_EXT_VALUE      {CHUNK_EXT_NAME}+ 


%%

 /*Initial state of LEX*/
<INITIAL>{METHOD} {
  yylval->__str = strdup(yytext);
  /*This is going to be HTTP REQuest.*/
  BEGIN(HTTP_REQ_ST);
  return(HTTP_METHOD);
}

 /*FSM for Response Status Line*/
<INITIAL>{PROTOCOL} {
  yylval->__str = strdup(yytext);
  /*This is going to be HTT RESponse.*/
  BEGIN(HTTP_RSP_ST);
  return(HTTP_VERSION);
}

 /*FSM For HTTP Request Line*/
<HTTP_REQ_ST>{SPACE} {
  return(SPACE);
}

 /*URI can be default URI meaning / or with Query String.*/
<HTTP_REQ_ST>{URI} {
  yylval->__str = strdup(yytext);
  BEGIN(QS_PARAM_ST);
  return(RESOURCE);
}

 /*Case- Just a URI without QS Parameters.*/
<QS_PARAM_ST>{SPACE} {
  BEGIN(HTTP_REQ_ST);
  return(SPACE);
}

<QS_PARAM_ST>{WHAT} {
  return('?');
}

<QS_PARAM_ST>{QS_PARAM} {
  yylval->__pField = strdup(yytext);
  return(PARAM);
}

<QS_PARAM_ST>{EQ} {
  BEGIN(QS_VALUE_ST);
  return('=');
}

<QS_VALUE_ST>{QS_VALUE} {
  yylval->__pValue = strdup(yytext);
  return(VALUE);
}

 /*Query String will be separated with &*/
<QS_VALUE_ST>{AMPERSAND} {
  BEGIN(QS_PARAM_ST);
}

<QS_VALUE_ST>{SPACE} {
  BEGIN(HTTP_REQ_ST);
  return(SPACE);
}

<HTTP_REQ_ST>{PROTOCOL} {
  yylval->__str = strdup(yytext);
  return(HTTP_VERSION);
}

<HTTP_REQ_ST>{CRLF} {
  BEGIN(MIME_PARAM_ST);
  return(CRLF);								
}

<HTTP_RSP_ST>{STATUS_CODE} {
  yylval->__status_code = atoi(yytext);
  return(STATUS_CODE);
}

<HTTP_RSP_ST>{SPACE} {
  return(SPACE);
}

 /*Reason-Phrase of Http-Response.*/
<HTTP_RSP_ST>{STATUS_STR} {
  yylval->__reason_phrase = strdup(yytext);
  return(REASON_PHRASE);
}

 /*End of Status Line.*/
<HTTP_RSP_ST>{CRLF} {
  BEGIN(MIME_PARAM_ST);
  /*! End of line */
  return(CRLF);								
}

<INITIAL><<EOF>> {
  printf("Parsed successfully\n");
  return(EOF);
}

<MIME_PARAM_ST><<EOF>> {
  printf("Parsed successfully\n");
  return(EOF);
}

<MIME_PARAM_ST>{MIME_PARAM} {
  yylval->__pField = strdup(yytext);
  return(PARAM);
}

<MIME_PARAM_ST>{COLON} {
  BEGIN(MIME_VALUE_ST);  
  return(':');
}

<MIME_VALUE_ST>{MIME_VALUE} {
  yylval->__pValue = strdup(yytext);
  return(VALUE);
}

<MIME_VALUE_ST>{BODY_START} {
  BEGIN(HTTP_BODY_ST);
  return(CRLF);
}

<MIME_VALUE_ST>{CRLF} {
  BEGIN(MIME_PARAM_ST);
  return(CRLF);
}

 /*! move to initial stae upon receipt of EOF - End-of-File*/
<HTTP_BODY_ST><<EOF>> {
  BEGIN(INITIAL);  
  return(EOF);
}

 /*! HTTP Body ends with single CRLF*/
<HTTP_BODY_ST>{CRLF} {
  /*!move to INITIAL state.*/    
  BEGIN(INITIAL);  
  return(CRLF);
}

<HTTP_BODY_ST>{CHUNK_LENGTH} {
  /*hex-string without 0x prefix.*/    
  yylval->__chunk_length = strtol(yytext, NULL, 16);
  BEGIN(HTTP_CHUNKED_BOBY_ST);
  return(CHUNK_LENGTH);
}

<HTTP_CHUNKED_BOBY_ST>{CHUNK_LENGTH} {
  /*hex-string without 0x prefix.*/    
  yylval->__chunk_length = strtol(yytext, NULL, 16);
  return(CHUNK_LENGTH);
}

<HTTP_CHUNKED_BOBY_ST>{CRLF} {
  return(CRLF);
}

<HTTP_CHUNKED_BOBY_ST>{HTTP_BODY} {
  /*HTTP body may or may not be terminated with '\0'*/    
  yylval->__str = malloc(yyleng + 1);
  assert(yylval->__str != NULL);
  memset(yylval->__str, 0, yyleng + 1);
  memcpy(yylval->__str, yytext, yyleng);
  return(lSTRING);
}

 /*HTTP Chunked Body will always end with 0 \r\n*/
<HTTP_CHUNKED_BOBY_ST>{ZERO} {
  BEGIN(INITIAL);
  return('0');
}

<HTTP_CHUNKED_BOBY_ST>';' {
  BEGIN(HTTP_EXT_CHUNK_NAME_ST);
  return(CHUNK_EXT);
}

<HTTP_EXT_CHUNK_NAME_ST>{CHUNK_EXT_NAME} {
  yylval->__pField = malloc(yyleng + 1);
  assert(yylval->__pField != NULL);
  memset(yylval->__pField, 0, yyleng + 1);
  memcpy(yylval->__pField, yytext, yyleng);
  return(PARAM);
}

<HTTP_EXT_CHUNK_NAME_ST>{CRLF} {
  BEGIN(HTTP_CHUNKED_BOBY_ST);  
  return(CRLF);
}

<HTTP_EXT_CHUNK_NAME_ST>{ZERO} {
  BEGIN(INITIAL);
  return('0');
}

<HTTP_CHUNKED_BOBY_ST>'=' {
  BEGIN(HTTP_EXT_CHUNK_VALUE_ST);
  return('=');
}

<HTTP_EXT_CHUNK_VALUE_ST>{CHUNK_EXT_VALUE} {
  yylval->__pValue = malloc(yyleng + 1);
  assert(yylval->__pValue != NULL);
  memset(yylval->__pValue, 0, yyleng + 1);
  memcpy(yylval->__pValue, yytext, yyleng);
  BEGIN(HTTP_CHUNKED_BOBY_ST);
  return(VALUE);
}

<HTTP_BODY_ST>{HTTP_BODY} {
  yylval->__str = malloc(yyleng + 1);
  assert(yylval->__str != NULL);
  memset(yylval->__str, 0, yyleng + 1);
  memcpy(yylval->__str, yytext, yyleng);
  return(lSTRING);
}


%%
