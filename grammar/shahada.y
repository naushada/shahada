%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shahada.tab.h"
#include "shahada.yy.h"

int yyerror(yyscan_t yyscanner, const char *s);
__http_message_t *__PMessage;
%}

/*! Copies this piece of code verbatim in header file*/
%code requires {
#include "shahada.h"
typedef void *yyscan_t;
}

%union {
  __http_message_t *__message;
  __http_qs_t      *__request_line;
  __http_status_t  *__status_line;
  __http_headers_t *__http_headers;
  __http_body_t    *__http_body;
  __qs_param_ttt   *__qs_param;
  __qs_param_t     *__qs;
  char           *__pField;
  char           *__pValue;
  char           *__str;
  char           *__reason_phrase;
  int            __status_code;
  int            __chunk_length;
}

/*! tokens are looked in lex file for pattern matching*/
%token <__str> lSTRING HTTP_METHOD HTTP_VERSION RESOURCE CRLF SPACE CHUNK_EXT
%token <__pField>  PARAM
%token <__pValue>  VALUE
%token <__status_code> STATUS_CODE
%token <__reason_phrase> REASON_PHRASE
%token <__chunk_length> CHUNK_LENGTH

%type <__qs_param> qs 
%type <__qs> qstring 
%type <__http_headers> mime_headers 
%type <__message> http_message
%type <__request_line> request_line 
%type <__status_line> status_line 
%type <__http_body> message_body 

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
   /*Chunked Message Body.*/
  | CHUNK_LENGTH CRLF lSTRING CRLF                    {$$ = __httpInsertChunkedBody(NULL,   $1, $3);}
  | CHUNK_LENGTH CRLF lSTRING CRLF '0'                {$$ = __httpInsertChunkedBody(NULL,   $1, $3);}
  | message_body CHUNK_LENGTH CRLF lSTRING CRLF       {$$ = __httpInsertChunkedBody($1, $2, $4);}
  | message_body CHUNK_LENGTH CRLF lSTRING CRLF '0'   {$$ = __httpInsertChunkedBody($1, $2, $4);}
   /*Chunked followed by chunk-extension.*/
  | CHUNK_LENGTH CHUNK_EXT PARAM CRLF lSTRING CRLF
  | CHUNK_LENGTH CHUNK_EXT PARAM CRLF lSTRING CRLF '0'
  | message_body CHUNK_LENGTH CHUNK_EXT PARAM CRLF lSTRING CRLF
  | message_body CHUNK_LENGTH CHUNK_EXT PARAM CRLF lSTRING CRLF '0'
   /*Chunked with optional chunked-value.*/
  | CHUNK_LENGTH CHUNK_EXT PARAM '=' VALUE CRLF lSTRING CRLF
  | CHUNK_LENGTH CHUNK_EXT PARAM '=' VALUE CRLF lSTRING CRLF '0'
  | message_body CHUNK_LENGTH CHUNK_EXT PARAM '=' VALUE CRLF lSTRING CRLF
  | message_body CHUNK_LENGTH CHUNK_EXT PARAM '=' VALUE CRLF lSTRING CRLF '0'
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
