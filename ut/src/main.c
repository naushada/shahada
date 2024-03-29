#include <stdio.h>
#include <stdlib.h>
#include "shahada.h"
#include "test.h"
#include "llog.h"


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
      case 7:
        __pBuff = __testHttpChunkedRsp("");
        break;
      case 8:
        __pBuff = __testHttpMultipleChunkedRsp("");
        break;
      case 9:
        __pBuff = __testHttpChunkedWithExtRsp("");
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

    //fprintf(stderr, "resource is %s\n", shahadaGetUri(pMsg));
    fprintf(stderr, "protocol is %d\n", shahadaGetProtocol(pMsg));
    //fprintf(stderr, "method is %d\n", shahadaGetMethod(pMsg));
    //fprintf(stderr, "value is %s\n", tt = shahadaGetQsParamValue("a", pMsg));
    //free(tt);

    if((ch - '0') == 9)
    {
      int len = 0;  
      char *outPtr = shahadaGetBody(1, pMsg, &len);
      DEBUG_PRINTF("", 0, "The Http Body is  >>>> %s len %d", outPtr, len);
      free(outPtr);

      outPtr = shahadaGetBody(0, pMsg, &len);
      DEBUG_PRINTF("", 0, "The Http Body is  >>>> %s len %d", outPtr, len);
      free(outPtr);
      outPtr = shahadaGetBody(3, pMsg, &len);
      DEBUG_PRINTF("", 0, "The Http Body is  >>>> %s len %d", outPtr, len);
      free(outPtr);
      outPtr = shahadaGetBody(7, pMsg, &len);
      DEBUG_PRINTF("", 0, "The Http Body is  >>>> %s len %d", outPtr, len);
      free(outPtr);
    }

    shahadaHttpParserEnd(pMsg);
  }while(1);
}
