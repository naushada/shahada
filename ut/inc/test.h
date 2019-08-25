#ifndef __TEST_H__
#define __TEST_H__

char *__testHttpReqPost(void);
char *__testHttpReqGet(void);
char *__testHtpRsp(void);
char *__testHttpReqWithQs(char *Qs);
char *__testHttpRspWithBody(char *body);
char *__testHttpReqWithBody(char *body);
int __getInput(void);
char *__testHttpChunkedRsp(char *body);
char *__testHttpMultipleChunkedRsp(char *body);
char *__testHttpChunkedWithExtRsp(char *);

#endif /*__TEST_H__*/
