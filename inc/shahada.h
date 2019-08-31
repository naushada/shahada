#ifndef __HTTP_H__
#define __HTTP_H__
/*!
	* @brief HTTP Data structure declaration and their definition
	* @dated 20-Apr-2019
	* */

#define __HTTP_MAX_URI_SIZE 512

typedef enum
{
  __OPTIONS,
  __GET,
  __HEAD,
  __POST,
  __PUT,
  __DELETE,
  __TRACE,
  __CONNECT,

}__http_method_t;

typedef enum
{
  __HTTP1dot0 = 1,
  __HTTP1dot1,
  __HTTP2dot0
}__http_version_t;

typedef struct
{
  __http_version_t __protocol;
  int __statusCode;
  char *__reasonPhrase;

}__http_status_t;

struct __http_method_t 
{
  __http_method_t __httpMethod;
  char *__pHttpMethodStr;
  char __strLen;
};

struct __http_version_t
{
  __http_version_t __httpVersion;
  char *__pVersionStr;
  char __strLen;
};

typedef struct __http_header 
{
  char *__field;
  char *__value;
}__http_header_t;

struct __http_headers
{
  __http_header_t *__header;  
  struct __http_headers *__next;
};

struct __qs_param
{
  char *__name;
  char *__value;
  struct __qs_param *__next;
};

typedef struct __qs_param __qs_param_t;

struct __qs_param_tt
{
  char *__resourceName;
  __qs_param_t *__qsParam;
};

typedef struct __qs_param_tt __qs_param_ttt;

struct __http_qs
{
  __http_method_t __method;
  __http_version_t __version;
  __qs_param_ttt *__qsParam;
  
};

struct __http_body
{
  int  __bodyLen;								
  char *__httpBody;
  char *__param;
  char *__value;
  struct __http_body *__next;		
};

typedef struct __http_qs __http_qs_t;
typedef struct __http_headers __http_headers_t;
typedef struct __http_body __http_body_t;

struct __http_req
{
  __http_qs_t      *__httpReq;
  __http_status_t  *__statusLine;
  __http_headers_t *__httpHeaders;
  __http_body_t    *__httpBody;
};

typedef struct __http_req __http_message_t;

__qs_param_ttt *__http_process_qs(char *pResource, __qs_param_t *pQs);

__http_qs_t *__httpRequestLine(char *pHttpMethod, 
                               __qs_param_ttt *pUri, 
                               char *pHttpVersion);

__http_header_t *__httpNewMimeHeader(char *pMimeFieldName, 
                                     char *pMimeFieldValue);

void __httpDisplay(__http_message_t *pHttpMessage);

__http_headers_t *__httpAddMimeHeader(__http_headers_t *headers, 
                                      __http_header_t *newNode);

__http_message_t *__httpReqMessage(__http_qs_t *reqLine, 
                                   __http_headers_t *header, 
                                   __http_body_t *body);

__http_message_t *__httpRspMessage(__http_status_t *statusLine,
                                   __http_headers_t *header,
                                   __http_body_t *body);

__http_status_t *__httpStatusLine(char *pHttpVersion, 
                                  int statusCode, 
                                  char *pReasonPhrase);

__http_headers_t *__httpInsertMimeHeader(__http_headers_t *headers, 
                                         char *field, 
                                         char *value);

__http_body_t *__httpInsertBody(__http_body_t *head, char *body);

__http_body_t *__httpInsertChunkedBody(__http_body_t *head, 
                                       int length, 
                                       char *body);

__http_body_t *__httpInsertChunkedWithToken(__http_body_t *head, 
                                            int length, 
                                            char *param,
                                            char *value,
                                            char *body);

__qs_param_t *__httpInsertQsParam(__qs_param_t *qsParam, 
                                  char *param, 
                                  char *value);

void *shahadaHttpParserStart(char *pIn);
void shahadaHttpParserEnd(void *handle);
char *shahadaGetFieldValue(char *field_name, void *msg);
char *shahadaGetUri(void *pMsg);
char *shahadaGetQsParamValue(char *qsParamName, void *pMsg);
char *shahadaGetReasonPhrase(void *pMsg);

int shahadaGetStatusCode(void *pMsg);
int shahadaGetMethod(void *pMsg);
int shahadaGetProtocol(void *pMsg);

void shahadaHttpParserEnd(void *pIn);

char *shahadaGetBody(int chunkNumber, void *pIn, int *chunkedLen);

#endif /*__HTTP_H__*/
