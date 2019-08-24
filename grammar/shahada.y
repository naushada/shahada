%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shahada.tab.h"
#include "shahada.yy.h"

int yyerror(yyscan_t yyscanner, const char *s);
http_message_t *__PMessage;
%}

/*! Copies this piece of code verbatim in header file*/
%code requires {
#include "shahada.h"
typedef void *yyscan_t;
}

%union {
  http_message_t *message;
  http_qs_t      *request_line;
  http_status_t  *status_line;
  http_headers_t *http_headers;
  http_body_t    *http_body;
  qs_param_ttt   *qs_param;
  qs_param_t     *qs;
  char           *pField;
  char           *pValue;
  char           *str;
  char           *reason_phrase;
  int            status_code;
  int            chunk_length;
}

/*! tokens are looked in lex file for pattern matching*/
%token <str> lSTRING HTTP_METHOD HTTP_VERSION RESOURCE CRLF SPACE
%token <pField>  PARAM
%token <pValue>  VALUE
%token <status_code> STATUS_CODE
%token <reason_phrase> REASON_PHRASE
%token <chunk_length> CHUNK_LENGTH

%type <qs_param> qs 
%type <qs> qstring 
%type <http_headers> mime_headers 
%type <message> http_message
%type <request_line> request_line 
%type <status_line> status_line 
%type <http_body> message_body 

%define parse.error verbose
%define parse.lac full
/*! For re-entrant parser*/
%define api.pure full
%param {yyscan_t yyscanner}

/*! Starting point of the Grammar*/
%start generic_message 

%%

generic_message
  : http_message  {__PMessage = $1;__httpDisplay($1);}
  ;

http_message
  : request_line                             {$$ = __httpReqMessage($1, NULL, NULL);}
  | request_line mime_headers                {$$ = __httpReqMessage($1, $2, NULL);}
  | request_line mime_headers message_body   {$$ = __httpReqMessage($1, $2, $3);}
  /*Grammar for HTTP Response.*/
  | status_line                              {$$ = __httpRspMessage($1, NULL, NULL);}
  | status_line mime_headers                 {$$ = __httpRspMessage($1, $2, NULL);}
  | status_line mime_headers message_body    {$$ = __httpRspMessage($1, $2, $3);}
  ;

message_body
  : lSTRING CRLF                                      {$$ = __httpInsertBody(NULL, $1);}
  | message_body lSTRING CRLF                         {$$ = __httpInsertBody($1,   $2);}
  | CHUNK_LENGTH CRLF lSTRING CRLF                    {$$ = __httpInsertChunkedBody(NULL,   $1, $3);}
  | CHUNK_LENGTH CRLF lSTRING CRLF '0'                {$$ = __httpInsertChunkedBody(NULL,   $1, $3);}
  | message_body CHUNK_LENGTH CRLF lSTRING CRLF       {$$ = __httpInsertChunkedBody($1, $2, $4);}
  | message_body CHUNK_LENGTH CRLF lSTRING CRLF '0'   {$$ = __httpInsertChunkedBody($1, $2, $4);}
  ; 

mime_headers
  : PARAM ':' VALUE CRLF                   {$$ = __httpInsertMimeHeader(NULL, $1, $3);} 
  | mime_headers PARAM ':' VALUE CRLF      {$$ = __httpInsertMimeHeader($1, $2, $4);}
  ;

request_line
  : HTTP_METHOD SPACE qs SPACE HTTP_VERSION CRLF {$$ = __httpRequestLine($1, $3, $5);}
  ;

qs
  : RESOURCE                  {$$ = __http_process_qs($1, NULL);}
  | RESOURCE '?' qstring      {$$ = __http_process_qs($1, $3);}
  ;

qstring
  : PARAM '=' VALUE            {$$ = __httpInsertQsParam(NULL, $1, $3);}
  | qstring PARAM '=' VALUE    {$$ = __httpInsertQsParam($1, $2, $4);}
  ;

status_line
  : HTTP_VERSION SPACE STATUS_CODE REASON_PHRASE CRLF {$$ = __httpStatusLine($1, $3, $5);}
  ;

%%

int yyerror(yyscan_t scanner, const char *s) {
  printf( "%s:%d Error: %s \n " , __FILE__, __LINE__,s);
  return(0);
}
