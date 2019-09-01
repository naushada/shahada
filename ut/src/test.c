#ifndef __TEST_C__
#define __TEST_C__
#include <string.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>


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
  setlocale(LC_ALL, "");
  wchar_t mc = 0x0628;
  mc = 0x062B;
  fprintf(stderr, "Naushad %lc\n", mc);
  fprintf(stderr, "1(%lc).......__testHttpReqPost \n"
                  "2(%lc).......__testHttpReqGet \n"
                  "3(%lc).......__testHtpRsp \n"
                  "4(%lc).......__testHttpReqWithQs \n"
                  "5(%lc).......__testHttpRspWithBody \n"
                  "6(%lc).......__testHttpReqWithBody \n"
                  "7(%lc).......__testHttpChunkedRsp \n"
                  "8(%lc).......__testHttpMultipleChunkedRsp \n"
                  "9(%lc).......__testHttpChunkedWithExtRsp \n"
                  "10(%lc%lc)......End \n",
                  0x06F1,
                  0x06F2,
                  0x06F3,
                  0x06F4,
                  0x06F5,
                  0x06F6,
                  0x06F7,
                  0x06F8,
                  0x06F9,
                  0x06F1,
                  0x06F0);
  return(getchar());

}

#endif /*__TEST_C__*/
