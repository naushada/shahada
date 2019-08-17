#include <stdio.h>
#include <stdlib.h>
#include "shahada.h"


int yydebug = 1;
int main(int argc, char **argv) {
    void *pMsg = NULL;
  /*! Read input from File now.*/
  char buff[2048] = "GET /asc.html HTTP/1.1\r\n"
                    "Host: 10.10.10.1\r\n"
                    "Content-Length: 101\r\n"
                    "Content-Type: json; txt/5.0\r\n"
                    "User-Agent: CERN-LineMode/2.15 libwww/2.17b3\r\n"
                    "Server: Apache/0.8.4\r\n"
                    "Accept: text/*, text/html, text/html;level=1, */*\r\n"
                    "\r\n\r\n"
                    "a=b&c=d\r\n";
#if 0
  char buff[2048] = "HTTP/1.1 200 OK\r\n"
                    "Host: 10.10.10.1\r\n"
                    "Content-Length: 101\r\n"
                    "Content-Type: json; txt/5.0\r\n"
                    "User-Agent: CERN-LineMode/2.15 libwww/2.17b3\r\n"
                    "Server: Apache/0.8.4\r\n"
                    "Accept: text/*, text/html, text/html;level=1, */*\r\n"
                    "\r\n\r\n"
                    "a=b&c=d\r\n";
#endif

  pMsg = __http_parser_ex(buff);
  char *fValue = shahadaGetFieldValue("Content-Length", pMsg);
  fprintf(stderr, "Value of Field is %s\n", fValue);
  fprintf(stderr, "resource is %s\n", shahadaGetUri(pMsg));
  fprintf(stderr, "protocol is %d\n", shahadaGetProtocol(pMsg));
  fprintf(stderr, "method is %d\n", shahadaGetMethod(pMsg));
  free(fValue);
  return(0);
}