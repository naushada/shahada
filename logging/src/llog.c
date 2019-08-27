#ifndef __LOG_C__
#define __LOG_C__

#include <stdio.h>
#include <syslog.h>
#include <string.h>
#include <libgen.h>

#include "llog.h"

const char *__logLevelStr[] = {
    "NA", "FTL", "CRT", "ERR", "WRN", "NTC", "INF"
};

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

  //syslog(syslogLevels[LOG_DEBUG], "%s", temp1);
  fprintf(stderr, "%s", temp1);
}

/*
 * @brief 
 * @param _tname is the Process Name 
 * @param _inst is the instance number of Process 
 * @param fmt is the format specifier along with string 
 * @return none.
 * */
void __logPrint(char *_tname, int _inst, const char * fmt, ...)
{
  char  temp[__LOG_BUFSIZE];
  char  baseFile[256];
  char  timeBuffer[40];
  va_list args;
  
  snprintf(baseFile, sizeof(baseFile),"%s",__FILE__);
  SYSTEM_TIMESTR(timeBuffer,40);

  va_start(args, fmt);
  vsnprintf(temp,
            __LOG_BUFSIZE,
            fmt, 
            args);
  va_end(args);

  fprintf(stderr,"[%s %s:%u %s:%u] " "%s\n",
          timeBuffer,
          _tname,
          _inst,
          basename(baseFile),
          __LINE__ ,
          temp);
}

#endif /*__LOG_C__*/
