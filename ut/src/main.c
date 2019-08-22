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
    /*ch is having ASCII value and by subtracting '0' gives numerical value.*/
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
    free(__pBuff);
    __pBuff = NULL;
    char *fValue = shahadaGetFieldValue("Content-Length", pMsg);
    fprintf(stderr, "Value of Field is %s\n", fValue);
    free(fValue);
    char *tt = NULL;

    //fprintf(stderr, "resource is %s\n", shahadaGetUri(pMsg));
    fprintf(stderr, "protocol is %d\n", shahadaGetProtocol(pMsg));
    //fprintf(stderr, "method is %d\n", shahadaGetMethod(pMsg));
    //fprintf(stderr, "value is %s\n", tt = shahadaGetQsParamValue("a", pMsg));
    //free(tt);

    shahadaHttpParserEnd(pMsg);
  }while(1);
}
