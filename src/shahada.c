#include <stdio.h>
#include <assert.h>
#include "shahada.tab.h"
#include "shahada.yy.h"
#include "shahada.h"
#include "llog.h"

/*
 * @brief This function is used to create the data structure for 
 *        HTTP-Response message.
 * @param  statusLine pointer to HTTP-Status Line which has HTTP/1.1 statusCode ReasonPhrase.
 * @param  headers is the pointer to MIME-Headers.
 * @param body is the pointer to http-body data structure.
 * @return pointer to http_message_t handle.
 * */
__http_message_t *__httpRspMessage(__http_status_t *statusLine, 
                                   __http_headers_t *headers,
                                   __http_body_t *body)
{
      
  __http_message_t *__httpRsp = NULL;
  __httpRsp = (__http_message_t *)malloc(sizeof(__http_message_t));
  assert(__httpRsp != NULL);

  memset((void *)__httpRsp, 0, sizeof(__http_message_t));

  __httpRsp->__statusLine   = statusLine;
  __httpRsp->__httpHeaders  = headers;
  __httpRsp->__httpBody     = body;

  return(__httpRsp);
}

/*
 * @brief 
 * @param 
 * @param 
 * @param 
 * @return 
 * */
__http_message_t *__httpReqMessage(__http_qs_t *reqLine, 
                                   __http_headers_t *headers,
                                   __http_body_t *body)
{
  __http_message_t *__httpReq = NULL;
  __httpReq = (__http_message_t *)malloc(sizeof(__http_message_t));

  /*assert when __httpReq is equal to NULL.*/
  assert(__httpReq != NULL);

  memset((void *)__httpReq, 0, sizeof(__http_message_t));

  __httpReq->__httpReq     = reqLine;
  __httpReq->__httpHeaders = headers;
  __httpReq->__httpBody    = body;

  return(__httpReq);
}

/*
 * @brief 
 * @param 
 * @param 
 * @param 
 * @return
 * */
__http_body_t *__httpInsertChunkedBody(__http_body_t *head, 
                                       int length, 
                                       char *body)
{
  __http_body_t *tmp = NULL;
  tmp = (__http_body_t *)malloc(sizeof(__http_body_t));
  assert(tmp != NULL);
  memset((void *)tmp, 0, sizeof(__http_body_t));

  tmp->__bodyLen = length;
  tmp->__httpBody = (char *)malloc(length);
  assert(tmp->__httpBody != NULL);
  memset((void *)tmp->__httpBody, 0, length);
  memcpy((void *)tmp->__httpBody, body, length);
  tmp->__next = NULL;
  free(body);

  if(!head)
  {
    return(tmp);    
  }

  __http_body_t *tt = head;
  for(; tt->__next; tt = tt->__next) ;

  tt->__next = tmp;
  return(head);
}

/*
 * @brief 
 * @param 
 * @param 
 * @param 
 * @param 
 * @param 
 * @return
 * */
__http_body_t *__httpInsertChunkedWithToken(__http_body_t *head, 
                                            int length, 
                                            char *param,
                                            char *value,
                                            char *body)
{
      
}
/*
 * @brief 
 * @param head 
 * @param body 
 * @return 
 * */
__http_body_t *__httpInsertBody(__http_body_t *head, char *body)
{
  __http_body_t *tmp = NULL;
  tmp = (__http_body_t *)malloc(sizeof(__http_body_t));
  /*assert when tmp is equal to NULL.*/
  assert(tmp != NULL);

  memset((void *)tmp, 0, sizeof(__http_body_t));
  tmp->__httpBody = strdup(body);
  tmp->__bodyLen = strlen(body);
  tmp->__next = NULL;
  free(body);

  if(!head)
  {
    return(tmp);
  }

  __http_body_t *m;
  for(m = head; m->__next; m = m->__next) ;

  m->__next = tmp;    
  return(head);
}

/*
 * @brief:
 * @param 
 * @param 
 * @param 
 * @return 
 * */
__http_status_t *__httpStatusLine(char *pHttpVersion, 
                                  int statusCode, 
                                  char *pReasonPhrase)
{
  __http_status_t *__pReq = NULL;

  struct __http_version_t __httpVersionArr[] =
  {
    {__HTTP1dot0, "HTTP/1.0", 8},
    {__HTTP1dot1, "HTTP/1.1", 8},
    {__HTTP2dot0, "HTTP/2.0", 8}
  };

  do 
  {
    if(!pHttpVersion)
    {
      /*Debug log to be added.*/ 
      DEBUG_LOG("Pointer to HTTP-Protocol is NULL");
      break;    
    }

    if(!pReasonPhrase)
    {
      /*Debug log to be added.*/  
      DEBUG_LOG("Pointer to HTTP-resaon-phrase is NULL");
      break;    
    }

    __pReq = (__http_status_t *)malloc(sizeof(__http_status_t));
    assert(__pReq != NULL); 

    memset((void *)__pReq, 0, sizeof(__http_status_t));

    /*Translating HTTP Verion*/
    int idx;
    for(idx = 0; idx <= __HTTP2dot0; idx++)
    {
      if(!strncmp(pHttpVersion, __httpVersionArr[idx].__pVersionStr, __httpVersionArr[idx].__strLen))
      {
        __pReq->__protocol = __httpVersionArr[idx].__httpVersion;
        break;
      }
    }

    free(pHttpVersion);
    __pReq->__statusCode = statusCode;
    __pReq->__reasonPhrase = strdup(pReasonPhrase);
    free(pReasonPhrase);

  }while(0);

  return(__pReq);
}

/*
 * @brief:
 * @param 
 * @param 
 * @param 
 * @return 
 * */
__http_qs_t *__httpRequestLine(char *pHttpMethod, 
                               __qs_param_ttt *pUri, 
                               char *pHttpVersion)
{
  __http_qs_t *__pReq = NULL;

  struct __http_method_t __httpMethodArr[] = 
  {
    {__OPTIONS, "OPTIONS", 7},
    {__GET,     "GET",     3},
    {__HEAD,    "HEAD",    4},
    {__POST,    "POST",    4},
    {__PUT,     "PUT",     3},
    {__DELETE,  "DELETE",  6},
    {__TRACE,   "TRACE",   5},
    {__CONNECT, "CONNECT", 7}
  };

  struct __http_version_t __httpVersionArr[] =
  {
    {__HTTP1dot0, "HTTP/1.0", 8},
    {__HTTP1dot1, "HTTP/1.1", 8},
    {__HTTP2dot0, "HTTP/2.0", 8}
  };

  do 
  {
    if(!pHttpMethod)
    {
      /*Debug log to be added.*/
      DEBUG_PRINTF("",0, "Pointer to the Http-Method is NULL");
      break;    
    }

    if(!pUri)
    {
      /*Debug log to be added.*/  
      DEBUG_PRINTF("",0, "Pointer to the Http-Uri is NULL");
      break;    
    }

    if(!pHttpVersion)
    {
      /*Debug log to be added.*/  
      DEBUG_PRINTF("",0, "Pointer to the Http-Version is NULL");
      break;
    }

    __pReq = (__http_qs_t *)malloc(sizeof(__http_qs_t));
    /*assert when __pReq is equal to NULL.*/
    assert(__pReq != NULL); 

    memset((void *)__pReq, 0, sizeof(__http_qs_t));
    /*Translating HTTP Method.*/
    int idx = 0;
    for(idx = 0; idx <= __CONNECT; idx++)
    {
      if(!strncmp(pHttpMethod, __httpMethodArr[idx].__pHttpMethodStr, __httpMethodArr[idx].__strLen))
      {
        __pReq->__method = __httpMethodArr[idx].__httpMethod;
        break;
      }
    }

    /*Translating HTTP Verion*/
    for(idx = 0; idx <= __HTTP2dot0; idx++)
    {
      if(!strncmp(pHttpVersion, __httpVersionArr[idx].__pVersionStr, __httpVersionArr[idx].__strLen))
      {
        __pReq->__version = __httpVersionArr[idx].__httpVersion;
        break;
      }
    }

    __pReq->__qsParam = pUri;
    free(pHttpMethod);
    pHttpMethod = NULL;
    free(pHttpVersion);
    pHttpVersion = NULL;

  }while(0);

  return(__pReq);
}

/*
 * @brief 
 * @param 
 * @param 
 * @Param 
 * @return 
 * */
__http_headers_t *__httpInsertMimeHeader(__http_headers_t *headers, char *field, char *value)
{
  return __httpAddMimeHeader(headers, __httpNewMimeHeader(field, value));
}

/*
 * @brief 
 * @param 
 * @param 
 * @return 
 * */
__http_headers_t *__httpAddMimeHeader(__http_headers_t *headers, __http_header_t *newNode)
{
  __http_headers_t *tmp = (__http_headers_t*)malloc(sizeof(__http_headers_t));
  assert(tmp != NULL);

  memset((void *)tmp, 0, sizeof(__http_headers_t));

  tmp->__header = newNode;
  tmp->__next = NULL;

  if(!headers) 
  {
    return tmp;
  }

  __http_headers_t *m;
  for(m = headers; m->__next; m = m->__next) {}
    m->__next = tmp;

  return headers;
}

/*
 * @brief 
 * @param 
 * @param 
 * @return 
 * */
__http_header_t *__httpNewMimeHeader(char *pMimeFieldName, 
                                     char *pMimeFieldValue)
{
  __http_header_t *fNode = NULL;

  do 
  {
    fNode = (__http_header_t*)malloc(sizeof(__http_header_t));
    assert(fNode != NULL); 

    memset((void *)fNode, 0, sizeof(__http_header_t));
    fNode->__field = strdup(pMimeFieldName);
    fNode->__value = strdup(pMimeFieldValue);
    free(pMimeFieldName);
    free(pMimeFieldValue);
    break;

  } while(0);

  return(fNode);
}

/*
 * @brief 
 * @param 
 * @return 
 * */
void __httpDisplay(__http_message_t *pHttpMessage)
{
  do 
  {
    if(!pHttpMessage)
    {
      /*Add the debug log.*/
      DEBUG_PRINTF("", 0, "Pointer to Http-Message is NULL");
      break;
    }
  
    /*Displaying http-request*/
    if(pHttpMessage->__httpReq)
    {
      DEBUG_LOG("Method %d Protocol Version %d ", 
              pHttpMessage->__httpReq->__method,
              pHttpMessage->__httpReq->__version);

      /*Query String if any.*/
      if(pHttpMessage->__httpReq->__qsParam)
      {
        DEBUG_LOG("URI is %s ", 
                pHttpMessage->__httpReq->__qsParam->__resourceName);
        __qs_param_t *tmp = pHttpMessage->__httpReq->__qsParam->__qsParam;

        while(tmp)
        {
          fprintf(stderr, "Param %s Value %s",
                  tmp->__name,tmp->__value);
          tmp = tmp->__next;
          fprintf(stderr, " ");
        }
        fprintf(stderr, "\n");
      }
    }

    /*Displaying status line.*/
    if(pHttpMessage->__statusLine)
    {
      DEBUG_LOG("Status code %d Protocol version %d ", 
              pHttpMessage->__statusLine->__statusCode,
              pHttpMessage->__statusLine->__protocol);
      if(pHttpMessage->__statusLine->__reasonPhrase)
      {
        DEBUG_LOG("Reason Phrase %s \n", pHttpMessage->__statusLine->__reasonPhrase);
      }
    }

    /*Displaying http-headers.*/
    __http_headers_t *tmpHeader = pHttpMessage->__httpHeaders;
    while(tmpHeader)
    {
      DEBUG_LOG("Field Name: %s Field Value: %s\n", 
              tmpHeader->__header->__field, 
              tmpHeader->__header->__value);

      tmpHeader = tmpHeader->__next;
    }
    DEBUG_LOG("\n");

    /*Displaying Http-Body*/
    if(pHttpMessage->__httpBody && pHttpMessage->__httpBody->__httpBody)
    {
      DEBUG_LOG("Http Body %s ",
              pHttpMessage->__httpBody->__httpBody);

      __http_body_t *tmp = pHttpMessage->__httpBody->__next;
      while(tmp)
      {
        DEBUG_LOG("Http Body %s ",
                tmp->__httpBody);
        tmp = tmp->__next; 
      }
    }
  }while(0);
}

/*
 * @brief 
 * @param 
 * @param 
 * @return 
 * */
__qs_param_ttt *__http_process_qs(char *pResource, __qs_param_t *pQs)
{
  __qs_param_ttt *qs_param = (__qs_param_ttt *)malloc(sizeof(__qs_param_ttt));
  /*Continue as long as qs_param is not NULL.*/
  assert(qs_param != NULL);

  do 
  {
    if(!pQs)
    {
      /*Only resource name is present.*/ 
      qs_param->__resourceName = strdup(pResource);
      qs_param->__qsParam = NULL;
      free(pResource);
      break;
    }

    qs_param->__resourceName = strdup(pResource);
    qs_param->__qsParam = pQs;
    free(pResource);

  }while(0);

  return(qs_param);		
}

/*
 * @brief 
 * @param 
 * @param 
 * @param 
 * @return 
 * */
__qs_param_t *__httpInsertQsParam(__qs_param_t *qsParam, 
                                  char *param, 
                                  char *value)
{
  __qs_param_t *tmpNode = NULL;
  tmpNode = (__qs_param_t *)malloc(sizeof(__qs_param_t));
  assert(tmpNode != NULL);
  memset((void *)tmpNode, 0, sizeof(__qs_param_t));

  tmpNode->__name = strdup(param);
  tmpNode->__value = strdup(value);
  tmpNode->__next = NULL;
  free(param);
  free(value);

  do 
  {
    if(!qsParam)
    {
      qsParam = tmpNode;
      qsParam->__next = NULL;
      break;
    }

    __qs_param_t *head = qsParam;
    for(; head->__next; head = head->__next) ;

    head->__next = tmpNode;
    break;

  }while(0);

  return(qsParam);
}

/*********************************************************
 *
 * Exposed API for application.
 *
 ********************************************************/

/*
 * @brief This function is to kick the http parsing of received http buffer
 *        The input buffer can contain HTTP-Request or HTTP-Response.
 * @param pIn Pointer to HTTP-Request/HTTP-Response with/without HTTP-Body.
 * @return It returns pointer to http_message_t typecasted to void * to remove
 *         dependency on Header.
 * */
void *shahadaHttpParserStart(char *pIn) 
{
  yyscan_t yyscanner;
  extern __http_message_t *__PMessage;

  if(yylex_init(&yyscanner))
  {
    fprintf(stderr, "%s:%d initialization to scanner failed\n", __FILE__, __LINE__);
    return((void *)0);
  }

  YY_BUFFER_STATE buff = pIn ? yy_scan_string(pIn, yyscanner) : 0;

  /*! Upon success, yyparse returns 0 and 1 upon failure.*/
  if(yyparse(yyscanner))
  {
    fprintf(stderr, "%s:%d yyparse failed\n", __FILE__, __LINE__);
    return((void *)0);    
  }

  yy_delete_buffer(buff, yyscanner);
  yylex_destroy(yyscanner);

  return((void *)__PMessage);
}

/*
 * @brief Once the HTTP Parsing is done successfully, This function can 
 *        be called/invoked to get MIME Header's Value.
 * @param field_name is the MIME Header Filed Name.
 * @param pMsg is the pointer to http_message_t which is returned once parsing was done 
 *             successfully by invoking function - shahadaHttpParserStart.
 * @return It returns pointer to char to the MIME-Value. and the caller of this Function
 *         shall release the memory.
 * */
char *shahadaGetFieldValue(char *field_name, void *pMsg)
{
  __http_message_t *msg = (__http_message_t *)pMsg;  
  __http_headers_t *head = msg ? msg->__httpHeaders: NULL; 
  char *fieldValue = NULL;

  do 
  {    
    if(!head)
    {
      fprintf(stderr, "Pointer to http_message_t is NULL");
      break;
    }

    while(head)
    {
      if(!strncmp(field_name, head->__header->__field, strlen(field_name)))
      {
        fieldValue = strdup(head->__header->__value);
        break;
      }
      head = head->__next;
    }

  }while(0);

  return(fieldValue);
}

/*
 * @brief This function is to return the HTTP-Method. 
 * @param msg is the pointer to http_message_t returned by invoking shahadaHttpParserStart
 * @return It returns the enumerated value of HTTP-Method.
 *         {OPTIONS = 0, GET, HEAD, POST,PUT, DELETE, TRACE, CONNECT}
 * */
int shahadaGetMethod(void *msg)
{
  __http_message_t *pMsg = (__http_message_t *)msg;  
  __http_qs_t *__req = pMsg ? pMsg->__httpReq: NULL;

  if(__req) return(__req->__method);

  return(-1);
}

/*
 * @brief This function is used to get the HTTP-Protocol. And the Protocol
 *        can be any of HTTP/1.0, HTTP/1.1 and HTTP/2.0
 * @param msg Pointer to http_message_t which is returned once HTTP Parsing is done successfully.
 * @return It return the enumerated value of HTTP-Protocol.
 * */
int shahadaGetProtocol(void *msg)
{
  __http_message_t *pMsg = (__http_message_t *)msg;  
  __http_qs_t *__req = pMsg ? pMsg->__httpReq: NULL;
  __http_status_t *__status = pMsg ? pMsg->__statusLine: NULL;

  if(__req) return(__req->__version);
  if(__status) return(__status->__protocol);

  return(-1);
}

/*
 * @brief This Function is used to get the HTTP Resource Name i.e. URI from HTTP-Request. 
 * @param msg is the pointer to http_message_t 
 * @return pointer to char of URI. and the caller shall free the memory.
 * */
char *shahadaGetUri(void *msg)
{
  __http_message_t *pMsg = (__http_message_t *)msg;  
  char *pUri = NULL;
  __http_qs_t *head = pMsg ? pMsg->__httpReq: NULL;

  if(!head) return((char *)0);

  pUri = strdup(head->__qsParam->__resourceName);
  return(pUri);
}

/*
 * @brief This function is used to get the Query String Parameter's value.
 *        Once the the parsing is successful.
 * @param qsParamName pointer to query string parameter name
 * @param msg is the pointer to the http_message_t
 * @return pointer to char of query string value. And the caller shall free the memory.
 * */
char *shahadaGetQsParamValue(char *qsParamName, void *msg)
{
  __http_message_t *pMsg = (__http_message_t *)msg;  
  char *pQsParam = NULL;
  __qs_param_t *head = NULL;

  if(pMsg && pMsg->__httpReq && pMsg->__httpReq->__qsParam)
  {
    head = pMsg ? pMsg->__httpReq->__qsParam->__qsParam: NULL;
  }
  else
  {
    return(pQsParam);
  }
        
  while(head)
  {
    if(!strncmp(qsParamName, head->__name, strlen(head->__name)))
    {
      pQsParam = strdup(head->__value);
      break;
    }

    head = head->__next;
  }

  return(pQsParam);
}

/*
 * @brief This function is used to get the Status code of HTTP-Response. 
 * @param msg pointer to the http_message_t
 * @return it returns the HTTP Status Code.
 * */
int shahadaGetStatusCode(void *msg)
{
  __http_message_t *pMsg = (__http_message_t *)msg;  
  __http_status_t *head = pMsg ? pMsg->__statusLine: NULL;
  return(head ? (int)head->__statusCode : -1);
}

/*
 * @brief This function is used to get the HTTP-Response Status String/Phrase.
 * @param msg is the pointer to the http_message_t
 * @return Pointer to char of reason phrase. And the caller must free the memory.
 * */
char *shahadaGetReasonPhrase(void *msg)
{
  __http_message_t *pMsg = (__http_message_t *)msg;  
  char *pReasonPhrase = NULL;
  __http_status_t *head = pMsg ? pMsg->__statusLine: NULL;
  
  if(!head)
  {
     return(pReasonPhrase);    
  }

  pReasonPhrase = strdup(head->__reasonPhrase);
  return(pReasonPhrase);
}

/*
 * @brief This function must be called once HTTP Request/Response processed so that
 *        shahada library can free the allocated memory.If not called then there shall be memory leak.
 * @param pIn is the pointer to http_message_t
 * @return none.
 * */
void shahadaHttpParserEnd(void *pIn)
{
  __http_message_t *pMsg = (__http_message_t *)pIn;
  do 
  {
    if(!pMsg)
      break;

    /*freeing http_request buffer.*/
    if(pMsg->__httpReq && pMsg->__httpReq->__qsParam)
    {
      if(pMsg->__httpReq->__qsParam->__resourceName)
      {
        free(pMsg->__httpReq->__qsParam->__resourceName);    
      }
      __qs_param_t *head = pMsg->__httpReq->__qsParam->__qsParam;
      __qs_param_t *tmp = NULL;

      while(head && head->__next)
      {
        tmp = head;
        head = head->__next;
        free(tmp->__name);
        free(tmp->__value);
        free(tmp);
      }
     
      if(head)
      {
        free(head->__name);
        free(head->__value);
        free(head);
      }
      free(pMsg->__httpReq->__qsParam);
      pMsg->__httpReq->__qsParam = NULL;
      free(pMsg->__httpReq);
      pMsg->__httpReq = NULL;
    }

    /*Freeing status line.*/
    if(pMsg->__statusLine && pMsg->__statusLine->__reasonPhrase)
    {
      free(pMsg->__statusLine->__reasonPhrase);      
      free(pMsg->__statusLine);      
    }

    /*freeing mime-headers.*/
    if(pMsg->__httpHeaders)
    {
      __http_headers_t *head = pMsg->__httpHeaders;
      __http_headers_t *tmp = NULL;

      while(head && head->__next)
      {
        tmp = head;
        head = head->__next;
        if(tmp->__header)
        {
          free(tmp->__header->__field);
          free(tmp->__header->__value);
          free(tmp->__header);
          free(tmp);
        }
      }

      if(head)
      {
        free(head->__header->__field);    
        free(head->__header->__value);
        free(head->__header);
        free(head);
      }
    }
    /*freeing http-body.*/

    if(pMsg->__httpBody)
    {
      __http_body_t *head = pMsg->__httpBody;
      __http_body_t *tmp = NULL;

      while(head && head->__next)
      {
        tmp = head;
        head = head->__next;
        if(tmp->__httpBody) free(tmp->__httpBody);
        free(tmp);
      }

      if(head && head->__httpBody)
      {
        free(head->__httpBody);
        free(head);
      }
    }

    /*free the message itself.*/
    free(pMsg);
  }while(0);

  /*Return the control explicitly.*/
  return;
}
