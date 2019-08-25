#ifndef __LOG_H__
#define __LOG_H__

#include <stdarg.h>

void __logRaw(const char *fileName, 
              int lineNumber, 
              const char *fmt, ...);
void disp(void);

#define __LOG_BUF256 (256)
#define __LOG_BUF512 (512)
#define __LOG_BUF1K  (1024)
#define __LOG_BUF2K  (2*__LOG_BUF1K)
#define __LOG_BUF4K  (4*__LOG_BUF1K)
#define __LOG_BUF8K  (8*__LOG_BUF1K)

#define __LOG_BUFSIZE   __LOG_BUF2K
#define __PRINT_BUFSIZE __LOG_BUF512

#define DEBUG_LOG(fmt, ...)\
{\
  __logRaw(__FILE__, __LINE__, fmt, ##__VA_ARGS__ );\
}


#endif /*__LOG_H__*/
