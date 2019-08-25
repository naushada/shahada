#ifndef __LOG_H__
#define __LOG_H__

#include <stdarg.h>
#include <time.h>
#include <libgen.h>
#include <sys/time.h>

typedef struct timeval  timeval_t;
typedef struct timespec timespec_t;
typedef struct tm       tm_t;

void __logRaw(const char *fileName, 
              int lineNumber, 
              const char *fmt, ...);

void __logPrint(char *_tname, int _inst, const char * fmt, ...);

#define TM_TO_STR     strftime
#define EPOCH_TO_STR  ctime_r

#define TIME_UTC   0
#define TIME_LOCAL 1

#define TIMEZONE_OFFSET  timezone
#define TZSET()          tzset()

#define EPOCH_TO_TM(_t,_tm,_ty) { \
  if ((_ty) == TIME_UTC) gmtime_r(_t,_tm); \
  else localtime_r(_t,_tm); \
}

#define TM_TO_EPOCH(_tm,_t,_ty) { \
  if ((_ty) == TIME_UTC) (_t) = (mktime(_tm)-TIMEZONE_OFFSET); \
  else (_t) = mktime(_tm); \
}

#define EPOCH_TO_STR_FMT(_buf,_sz,_fmt,_t,_ty) { \
  tm_t _tm; \
  EPOCH_TO_TM((time_t*)_t,&_tm,_ty); \
  TM_TO_STR(_buf,_sz,_fmt,&_tm); \
}

#define TIMEVAL_TO_STR_FMT(_buf,_sz,_fmt,_tv,_ty) { \
  char tmpbuf[64]; \
  EPOCH_TO_STR_FMT(tmpbuf,64,_fmt,&(_tv)->tv_sec,_ty); \
  snprintf(_buf,_sz,"%s.%06lu",tmpbuf,(_tv)->tv_usec); \
}

#define SYSTEM_TIMESTR(_buf,_sz) { \
    timeval_t _tv; \
    SYSTEM_TIMEVAL(&_tv); \
    TIMEVAL_TO_STR_FMT(_buf,_sz,"%F %T",&_tv,TIME_LOCAL); \
}

#define __SYS_CLOCK    (CLOCK_MONOTONIC_RAW)
#define ___PROC_CLOCK  (CLOCK_PROCESS_CPUTIME_ID)

#define SYSTEM_EPOCH()          (UniTime)time(0)
#define SYSTEM_TIMEVAL(_t)      gettimeofday((_t),NULL)
#define SYSTEM_CLOCK(_ts)       clock_gettime(__SYS_CLOCK,(_ts))
#define SYSTEM_PROC_CLOCK(_ts)  clock_gettime(__PROC_CLOCK,(_ts))

#define SYSTEM_CLOCK_NSEC() ({   \
    UniTimespec rawts;           \
    SYSTEM_CLOCK(&rawts);        \
    (TIMESPEC_TO_NSECS(&rawts)); \
})

#define __LOG_LEVEL_ISVALID(_l) \
    ((_l) > __LOGLEVEL_NONE && (_l) < __LOGLEVEL_LAST)

#define __LOG_LEVEL_NAME(_l) \
    ((__LOG_LEVEL_ISVALID(_l))? __logLevelStr[(_l)]: "INV")

#define __LOG_ID(tok)    __LOG_ID_##tok
#define __LOG_LEV(tok)   __LOG_LEV_##tok
#define __LOG_MOD(tok)   __LOG_MOD_##tok
#define __LOG_OPTS(tok)  __LOG_OPTS_##tok
#define __LOG_FMT(tok)   __LOG_FMT_##tok

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

#define DEBUG_PRINTF(_tname,_inst, fmt, ...) { \
  __logPrint(_tname, _inst, fmt, ##__VA_ARGS__);\
}



#endif /*__LOG_H__*/
