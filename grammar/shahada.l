%{
#include <stdio.h>
#include <stdlib.h>
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


 /*Exclusive State for String Matching*/
%x MIME_PARAM_SCAN MIME_PARAM_VALUE_SCAN 
%x MESSAGE_BODY_SCAN_START MIME_DELIMITER 
%x MIME_VALUE_DELIMITER
%x HTTP_REQ HTTP_RSP QS_RES QS_RES_VALUE

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
 /*Any Character except : which is the delimeter of FIELD*/
NOT_COLON            [^:]
DELIMITER            [:][ ]
 /*Any character except \r*/
NOT_CR               [^\r]
BODY_START           (\r\n\r\n\r\n|\r\n\r\n)
URI                  \/{ALPHANUM}*
RES                  ^\/{ALPHANUM}+/\?
 /*URI                  [^\?]\?*/
URI_DELIMETER        [?][ ]
QS_PARAM             {ALPHANUM}+
QS_PARAM_DELIMITER   =
QS_VALUE             {ALPHANUM}+
NOT_SPACE            [^ ]
RESOURCE             ([ALPHANUM]*)[ ]
WHAT                 (\?)
AMPERSAND            (&)
MIME_PARAM           {ALPHANUM}+
COLON                (:)


%%

 /*Initial state of LEX*/
<INITIAL>{METHOD} {
  yylval->str = strdup(yytext);
  BEGIN(HTTP_REQ);
  return(HTTP_METHOD);
}

 /*FSM For HTTP Request Line*/
<HTTP_REQ>{SPACE} {
  return(SPACE);
}

<HTTP_REQ>{URI} {
  yylval->str = strdup(yytext);
  fprintf(stderr, "[Naushad] Moving to QS_RES State %s\n", yytext);
  BEGIN(QS_RES);
  return(RESOURCE);
}

<QS_RES>{WHAT} {
  return('?');
}

<QS_RES>{QS_PARAM} {
  fprintf(stderr, "[Naushad] QS-Param is %s\n", yytext);
  yylval->pField = strdup(yytext);
  return(PARAM);
}

<QS_RES>{EQ} {
  BEGIN(QS_RES_VALUE);
  return('=');
}

<QS_RES_VALUE>{QS_VALUE} {
  fprintf(stderr, "[Naushad] QS_RES_VALUE is %s\n", yytext);
  yylval->pValue = strdup(yytext);
  return(VALUE);
}

<QS_RES_VALUE>{AMPERSAND} {
  BEGIN(QS_RES);
}

<QS_RES_VALUE>{SPACE} {
  BEGIN(HTTP_REQ);
  return(SPACE);
}

<HTTP_REQ>'?' {
  return('?');
}

<HTTP_REQ>{PROTOCOL} {
  yylval->str = strdup(yytext);
  return HTTP_VERSION;
}

<HTTP_REQ>{CRLF} {
  BEGIN MIME_PARAM_SCAN;
  /*! End of line */
  return CRLF;								
}

 /*FSM for Response Status Line*/
<INITIAL>{PROTOCOL} {
  yylval->str = strdup(yytext);
  BEGIN(HTTP_RSP);
  fprintf(stderr, "\nMoving to HTTP_RSP value %s len %d\n", yytext,(int)yyleng);
  return(HTTP_VERSION);
}

<HTTP_RSP>{SPACE} {
  return(SPACE);
}

<HTTP_RSP>{DIGIT}{3} {
  yylval->status_code = atoi(yytext);
  return (STATUS_CODE);
}

 /*Reason-Phrase of Http-Response.*/
<HTTP_RSP>{NOT_CR}+ {
  yylval->reason_phrase = strdup(yytext);
  fprintf(stderr, "stderr, The value of Reason Phrase is %s\n", yytext);
  return (REASON_PHRASE);
}

 /*End of Status Line.*/
<HTTP_RSP>{CRLF} {
  BEGIN MIME_PARAM_SCAN;
  /*! End of line */
  return CRLF;								
}

<INITIAL><<EOF>> {
  printf("Parsed successfully\n");
  return EOF;
}

<MIME_PARAM_SCAN><<EOF>> {
  printf("Parsed successfully\n");
  return EOF;
}

<MIME_PARAM_SCAN>{MIME_PARAM} {
  yylval->pField = strdup(yytext);
  return(PARAM);
}

<MIME_PARAM_SCAN>{COLON} {
  BEGIN(MIME_PARAM_VALUE_SCAN);  
  return(':');
}

<MIME_DELIMITER>{DELIMITER}+ {
  BEGIN MIME_PARAM_VALUE_SCAN;
  return(SPACE);
}

<MIME_PARAM_VALUE_SCAN>{NOT_CR}+ {
  BEGIN MIME_VALUE_DELIMITER;
  yylval->pValue = strdup(yytext);
  return(VALUE);
}

<MIME_VALUE_DELIMITER>{BODY_START} {
  BEGIN MESSAGE_BODY_SCAN_START;
  return(CRLF);
}

<MIME_VALUE_DELIMITER>{CRLF} {
  BEGIN MIME_PARAM_SCAN;
  return(CRLF);
}

 /*! move to initial stae upon receipt of EOF - End-of-File*/
<MESSAGE_BODY_SCAN_START><<EOF>> {
  BEGIN INITIAL;  
  return(EOF);
}

 /*! HTTP Body ends with single CRLF*/
<MESSAGE_BODY_SCAN_START>{CRLF} {
  /*!move to INITIAL state.*/    
  BEGIN INITIAL;  
  return(CRLF);
}

<MESSAGE_BODY_SCAN_START>{NOT_CR}+ {
  yylval->str = strdup(yytext);
  return(lSTRING);
}


%%
