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
  char buff[2048] = "POST /abc.html?aa=xx&bb=cc&xx=a/b/c/d/e HTTP/1.1\r\n"
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

char *__testHttpMultipleChunkedRsp(char *body)
{
  char buff[2048] = "HTTP/1.1 200 OK\r\n"
                    "Host: 10.10.10.1\r\n"
                    "Content-Type: json; txt/5.0\r\n"
                    "User-Agent: CERN-LineMode/2.15 libwww/2.17b3\r\n"
                    "Server: Apache/0.8.4\r\n"
                    "Accept: text/*, text/html, text/html;level=1, */*\r\n"
                    "\r\n\r\n"
                    "1E\r\n"
                    "a=b&c=d&x=zzzzzzyyyyzzzyyyzzyy\r\n"
                    "1E\r\n"
                    "mma=b&c=d&x=zzzzzzyyyyzzzyyyzzyy\r\n"
                    "0\r\n";

  return(strdup(buff));
}


char *__testHttpChunkedRsp(char *body)
{
  char buff[2048] = "HTTP/1.1 200 OK\r\n"
                    "Host: 10.10.10.1\r\n"
                    "Content-Type: json; txt/5.0\r\n"
                    "User-Agent: CERN-LineMode/2.15 libwww/2.17b3\r\n"
                    "Server: Apache/0.8.4\r\n"
                    "Accept: text/*, text/html, text/html;level=1, */*\r\n"
                    "\r\n\r\n"
                    "1E\r\n"
                    "a=b&c=d&x=zzzzzzyyyyzzzyyyzzyy\r\n"
                    "0\r\n";

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
                    "a=b&c=d Hello Exp !\r\n";

  return(strdup(buff));
}

char *__testHttpChunkedWithExtRsp(char *body)
{
  char buff[] = "HTTP/1.1 200 OK\r\n"
                "Server: test\r\n"
                "Trailer: Expires, Content-MD5\r\n"
                "Transfer-Encoding: chunked\r\n"
                "\r\n"
                "5\r\n"
                "First\r\n"
                "d\r\n"
                "Hello, world!\r\n"
                "e\r\n"
                "The Next Chunk\r\n"
                "8\r\n"
                "Last one\r\n"
                "0\r\n";

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
                  "7.......__testHttpChunkedRsp \n"
                  "8.......__testHttpMultipleChunkedRsp \n"
                  "9.......__testHttpChunkedWithExtRsp \n"
                  "10......End \n");
  return(getchar());

}

#endif /*__TEST_C__*/
