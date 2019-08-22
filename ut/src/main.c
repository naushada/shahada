#include <stdio.h>
#include <stdlib.h>
#include "shahada.h"
#include "test.h"


int yydebug = 1;

int main(int argc, char **argv) 
{
  void *pMsg = NULL;
  char *__pBuff = NULL;
  int ch;
  do 
  {
    ch = __getInput();

    switch(ch - '0')
    {
      case 1:
        __pBuff = __testHttpReqPost();
        break;
      case 2:
        __pBuff = __testHttpReqGet();
        break;
      case 3:
        __pBuff = __testHtpRsp();
        break;
      case 4:
        __pBuff = __testHttpReqWithQs("");
        break;
      case 5:
        __pBuff = __testHttpRspWithBody("");
        break;
      case 6:
        __pBuff = __testHttpReqWithBody("");
        break;
      default:
        return(0);
    }

    pMsg = shahadaHttpParserStart(__pBuff);
    char *fValue = shahadaGetFieldValue("Content-Length", pMsg);
    fprintf(stderr, "Value of Field is %s\n", fValue);
    free(fValue);

    fprintf(stderr, "resource is %s\n", shahadaGetUri(pMsg));
    fprintf(stderr, "protocol is %d\n", shahadaGetProtocol(pMsg));
    fprintf(stderr, "method is %d\n", shahadaGetMethod(pMsg));
    fprintf(stderr, "value is %s\n", shahadaGetQsParamValue("a", pMsg));
  }while(1);
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
