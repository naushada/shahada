#ifndef __LOG_C__
#define __LOG_C__

#include <stdio.h>
#include <syslog.h>
#include <string.h>
#include <libgen.h>

#include "llog.h"

int syslogLevels[] = {
    LOG_DEBUG,    
    LOG_ALERT,    
    LOG_CRIT,     
    LOG_ERR,      
    LOG_WARNING,  
    LOG_NOTICE,   
    LOG_INFO     
};

void __logRaw(const char *fileName, 
              int lineNumber, 
              const char * fmt, ...)
{
  char  temp1[__LOG_BUFSIZE];
  char  baseFile[__LOG_BUFSIZE/2];
  int index;

  strcpy(baseFile, fileName);

  index = snprintf (temp1, __LOG_BUFSIZE,
                    "%s : %d: ",
                    basename(baseFile),
                    lineNumber);

  if (index < __LOG_BUFSIZE)
  {
    va_list args;
    va_start(args, fmt);
    vsnprintf(&temp1[index],
             (__LOG_BUFSIZE-index),
             fmt, args);
    va_end(args);
  }

  syslog(syslogLevels[LOG_DEBUG], "%s\n", temp1);
}

#endif /*__LOG_C__*/
