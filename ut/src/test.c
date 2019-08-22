#ifndef __TEST_C__
#define __TEST_C__
#include <string.h>
#include <stdio.h>

char *__testHttpReqPost(void)
{
  char *pBuff = NULL;

  char buff[2048] = "POST /abc.html HTTP/1.1\r\n"
                    "Host: 10.10.10.1\r\n"
                    "Content-Length: 101\r\n"
                    "Content-Type: json; txt/5.0\r\n"
                    "User-Agent: CERN-LineMode/2.15 libwww/2.17b3\r\n"
                    "Server: Apache/0.8.4\r\n"
                    "Accept: text/*, text/html, text/html;level=1, */*\r\n"
                    "\r\n\r\n"
                    "a=b&c=d\r\n";

  pBuff = strdup(buff);
  return(pBuff);
}

char *__testHttpReqGet(void)
{
  char buff[2048] = "POST / HTTP/1.1\r\n"
                    "Host: 10.10.10.1\r\n"
                    "Content-Length: 101\r\n"
                    "Content-Type: json; txt/5.0\r\n"
                    "User-Agent: CERN-LineMode/2.15 libwww/2.17b3\r\n"
                    "Server: Apache/0.8.4\r\n"
                    "Accept: text/*, text/html, text/html;level=1, */*\r\n"
                    "\r\n\r\n";

  return(strdup(buff));
}

char *__testHtpRsp(void)
{
  char buff[2048] = "HTTP/1.1 200 OK\r\n"
                    "Host: 10.10.10.1\r\n"
                    "Content-Length: 101\r\n"
                    "Content-Type: json; txt/5.0\r\n"
                    "User-Agent: CERN-LineMode/2.15 libwww/2.17b3\r\n"
                    "Server: Apache/0.8.4\r\n"
                    "Accept: text/*, text/html, text/html;level=1, */*\r\n"
                    "\r\n\r\n";

  return(strdup(buff));
}

char *__testHttpReqWithQs(char *Qs)
{
  char buff[2048] = "POST /abc.html?aa=xx&bb=cc HTTP/1.1\r\n"
                    "Host: 10.10.10.1\r\n"
                    "Content-Length: 101\r\n"
                    "Content-Type: json; txt/5.0\r\n"
                    "User-Agent: CERN-LineMode/2.15 libwww/2.17b3\r\n"
                    "Server: Apache/0.8.4\r\n"
                    "Accept: text/*, text/html, text/html;level=1, */*\r\n"
                    "\r\n\r\n";

  return(strdup(buff));
      
}

char *__testHttpRspWithBody(char *body)
{
  char buff[2048] = "HTTP/1.1 200 OK\r\n"
                    "Host: 10.10.10.1\r\n"
                    "Content-Length: 101\r\n"
                    "Content-Type: json; txt/5.0\r\n"
                    "User-Agent: CERN-LineMode/2.15 libwww/2.17b3\r\n"
                    "Server: Apache/0.8.4\r\n"
                    "Accept: text/*, text/html, text/html;level=1, */*\r\n"
                    "\r\n\r\n"
                    "a=b&c=d&x=zzzzzzyyyyzzzyyyzzyy\r\n";

  return(strdup(buff));
}

char *__testHttpReqWithBody(char *body)
{
  char buff[2048] = "POST /abc.html HTTP/1.1\r\n"
                    "Host: 10.10.10.1\r\n"
                    "Content-Length: 101\r\n"
                    "Content-Type: json; txt/5.0\r\n"
                    "User-Agent: CERN-LineMode/2.15 libwww/2.17b3\r\n"
                    "Server: Apache/0.8.4\r\n"
                    "Accept: text/*, text/html, text/html;level=1, */*\r\n"
                    "\r\n\r\n"
                    "a=b&c=d\r\n";

  return(strdup(buff));
}

int __getInput(void)
{
  fprintf(stderr, "1.......__testHttpReqPost \n"
                  "2.......__testHttpReqGet \n"
                  "3.......__testHtpRsp \n"
                  "4.......__testHttpReqWithQs \n"
                  "5.......__testHttpRspWithBody \n"
                  "6.......__testHttpReqWithBody \n"
                  "7.......End \n");
  return(getchar());

}

#endif /*__TEST_C__*/
