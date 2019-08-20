#include <stdio.h>
#include <stdlib.h>
#include "shahada.h"
#include "test.h"


int yydebug = 1;

int main(int argc, char **argv) 
{
  void *pMsg = NULL;
  char *__pBuff = NULL;
  __pBuff = __testHttpReqWithBody("aa=vv");
  pMsg = shahadaHttpParserStart(__pBuff);
  char *fValue = shahadaGetFieldValue("Content-Length", pMsg);
  fprintf(stderr, "Value of Field is %s\n", fValue);
  free(fValue);

  fprintf(stderr, "resource is %s\n", shahadaGetUri(pMsg));
  fprintf(stderr, "protocol is %d\n", shahadaGetProtocol(pMsg));
  fprintf(stderr, "method is %d\n", shahadaGetMethod(pMsg));
  fprintf(stderr, "value is %s\n", shahadaGetQsParamValue("a", pMsg));

  return(0);
}
