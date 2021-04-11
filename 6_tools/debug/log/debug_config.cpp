/*******************************************************************************

  Pilot Intelligence Library
    http://www.pilotintelligence.com/

  ----------------------------------------------------------------------------

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>

#include <string>
#include <vector>
#include <algorithm>

#include "base/Svar/Svar.h"
#include "base/utils/utils_str.h"
#include "debug_config.h"

using namespace std;


namespace pi {


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// debug level 
static int  g_iDebugLevel = 4;

// debug level stack
#define DEBUG_LEVE_STACK_SIZE 128

static int  g_aDebugLevelStack[DEBUG_LEVE_STACK_SIZE];
static int  g_iDebugLevelStackIdx=0;


/** 
 *  Set level of debug print
 *
 *  Parameters:
 *      \param[in]  i       level
 */
void dbg_set_level(int i)
{
    g_iDebugLevel = i;
    svar.GetInt("DBG_LEVEL", 4) = g_iDebugLevel;
} 

/**
 *  Get current debug level
 *
 *  Return value:
 *      current debug level
 */
int  dbg_get_level(void)
{
    g_iDebugLevel = svar.GetInt("DBG_LEVEL", 4);
    return g_iDebugLevel;
}

/**
 *  Push a new debug level to stack
 *
 *  FIXME:
 *      Not implementated yet
 *
 *  Paramters:
 *      \param[in]  i       new debug level
 *  Return value:
 *      None
 */
void dbg_push_level(int level)
{
    if( g_iDebugLevelStackIdx >= DEBUG_LEVE_STACK_SIZE ) {
        dbg_pe("Debug level stack overfull!");
        return;
    }

    g_aDebugLevelStack[g_iDebugLevelStackIdx++] = g_iDebugLevel;
    g_iDebugLevel = level;
    svar.GetInt("DBG_LEVEL", 4) = g_iDebugLevel;
}

/**
 *  Pop top debug level from stack
 *
 *  FIXME:
 *      Not implementated yet
 *
 *  Paramters:
 *      None
 *  Return value:
 *      new debug level
 */
int  dbg_pop_level(void)
{
    if( g_iDebugLevelStackIdx <= 0 ) {
        dbg_pe("Debug level stack is empty!");
        return g_iDebugLevel;
    }

    g_iDebugLevel = g_aDebugLevelStack[--g_iDebugLevelStackIdx];
    svar.GetInt("DBG_LEVEL", 4) = g_iDebugLevel;

    return g_iDebugLevel;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

typedef std::map<std::string, LogInfo_Message_Handle> LogInfoMessageHandleMap;
LogInfoMessageHandleMap g_logInfoMsgHandleMap;


int dbg_registMessageHandle(const std::string &handleName, LogInfo_Message_Handle &msgHandle)
{
    LogInfoMessageHandleMap::iterator it;

    it = g_logInfoMsgHandleMap.find(handleName);
    if( it == g_logInfoMsgHandleMap.end() ) {
        g_logInfoMsgHandleMap.insert(make_pair(handleName, msgHandle));
    } else {
        it->second = msgHandle;
    }

    return 0;
}

int dbg_unregistMessageHandle(const std::string &handleName)
{
    LogInfoMessageHandleMap::iterator it;

    it = g_logInfoMsgHandleMap.find(handleName);
    if( it == g_logInfoMsgHandleMap.end() ) {
        return -1;
    } else {
        g_logInfoMsgHandleMap.erase(it);
    }

    return 0;
}



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


inline char *_str_cat(char *s_out, const char *s1, const char *s2, const char *s3)
{
    int     i, j, l1, l2, l3;

    l1 = strlen(s1);
    l2 = strlen(s2);
    l3 = strlen(s3);

    j = 0;
    for(i=0; i<l1; i++) s_out[j++] = s1[i];
    for(i=0; i<l2; i++) s_out[j++] = s2[i];
    for(i=0; i<l3; i++) s_out[j++] = s3[i];
    s_out[j] = 0;

    return s_out;
}


#if defined(PIL_WINDOWS) || defined(PIL_MINGW)

inline void printHeaderTail(int level,
                     char *sHeader, char *sTail,
                     char *sHeader2, char *sTail2,
                     int line, const char *fname, const char *func)
{
    if( level == 1 ) {
        sprintf(sHeader, "ERR:  ");
        sprintf(sTail,   "    (LINE: %5d, FILE: %s, FUNC: %s)", line, fname, func);

        sprintf(sHeader2, "ERR:  ");
        sTail2[0] = 0;
    } else if (level == 2 ) {
        sprintf(sHeader, "WARN: ");
        sprintf(sTail,   "    (LINE: %5d, FILE: %s, FUNC: %s)", line, fname, func);

        sprintf(sHeader2, "WARN: ");
        sTail2[0] = 0;
    } else if (level == 3 ) {
        sprintf(sHeader, "INFO: ");
        sprintf(sTail,   "    (LINE: %5d, FILE: %s, FUNC: %s)", line, fname, func);

        sprintf(sHeader2, "INFO: ");
        sTail2[0] = 0;
    } else if (level == 4 ) {
        sprintf(sHeader, "%s >> ", func);
        sTail[0] = 0;

        sprintf(sHeader2, "TRAC: ");
        sTail2[0] = 0;
    } else {
        sHeader[0] = 0;
        sTail[0] = 0;

        sHeader2[0] = 0;
        sTail2[0] = 0;
    }
}

#endif

#if defined(PIL_LINUX)

inline void printHeaderTail(int level,
                     char *sHeader, char *sTail,
                     char *sHeader2, char *sTail2,
                     int line, const char *fname, const char *func)
{
    if( level == 1 ) {
        sprintf(sHeader, "\033[31mERR:\033[0m  ");
        sprintf(sTail,   "    \033[35m(LINE: %5d, FILE: %s, FUNC: %s)\033[0m", line, fname, func);

        sprintf(sHeader2, "ERR:  ");
        sTail2[0] = 0;
    } else if (level == 2 ) {
        sprintf(sHeader, "\033[33mWARN:\033[0m ");
        sprintf(sTail,   "    \033[35m(LINE: %5d, FILE: %s, FUNC: %s)\033[0m", line, fname, func);

        sprintf(sHeader2, "WARN: ");
        sTail2[0] = 0;
    } else if (level == 3 ) {
        sprintf(sHeader, "\033[36mINFO:\033[0m ");
        sprintf(sTail,   "    \033[35m(LINE: %5d, FILE: %s, FUNC: %s)\033[0m", line, fname, func);

        sprintf(sHeader2, "INFO: ");
        sTail2[0] = 0;
    } else if (level == 4 ) {
        sprintf(sHeader, "\033[34m%s\033[0m >> ", func);
        sTail[0] = 0;

        sprintf(sHeader2, "TRAC: ");
        sTail2[0] = 0;
    } else {
        sHeader[0] = 0;
        sTail[0] = 0;

        sHeader2[0] = 0;
        sTail2[0] = 0;
    }
}

#endif

void dbg_printf(int level,
               const char *fname, int line, const char *func,
               const char *szFmtString, ...)
{
    #define MAX_DBUG_BUFF_LEN    4096

    char    sHeader[MAX_DBUG_BUFF_LEN];
    char    sTail[MAX_DBUG_BUFF_LEN];

    char    sHeader2[MAX_DBUG_BUFF_LEN];
    char    sTail2[MAX_DBUG_BUFF_LEN];

    char    sBuf1[MAX_DBUG_BUFF_LEN];
    char    sBuf2[MAX_DBUG_BUFF_LEN];

    int     lBuf1, lBuf2;

    va_list va_params;

    // check debug level
    if( level > svar.GetInt("DBG_LEVEL", 4) ) return;

    // alloc string buffer
    lBuf1 = strlen(szFmtString);

    // generate header, tail
    printHeaderTail(level,
                    sHeader, sTail,
                    sHeader2, sTail2,
                    line, fname, func);

    // generate format string
    va_start(va_params, szFmtString);
    vsprintf(sBuf1, szFmtString, va_params);
    va_end(va_params);

    lBuf1 = strlen(sBuf1);
    if( lBuf1 > 0 && level < 4 )
        if( sBuf1[lBuf1-1] != '\n' ) {
            sBuf1[lBuf1] = '\n';
            sBuf1[lBuf1+1] = 0;
        }

    // concatenate final string
    _str_cat(sBuf2, sHeader, sBuf1, sTail);

    lBuf2 = strlen(sBuf2);
    if( lBuf2 > 0 ) {
        if( sBuf2[lBuf2-1] == '\n' ) sBuf2[lBuf2-1] = 0;
    }

    // output message
    puts(sBuf2);
    fflush(stdout);

    // output log information to registed call-back functions
    if( g_logInfoMsgHandleMap.size() > 0 ) {
        // concatenate final string
        _str_cat(sBuf2, sHeader2, sBuf1, sTail2);

        lBuf2 = strlen(sBuf2);
        if( lBuf2 > 0 ) {
            if( sBuf2[lBuf2-1] == '\n' ) sBuf2[lBuf2-1] = 0;
        }

        StringArray sa = split_line(sBuf2);

        // call call-back function
        for(LogInfoMessageHandleMap::iterator it=g_logInfoMsgHandleMap.begin(); it!=g_logInfoMsgHandleMap.end(); it++) {
            for(int i=0; i<sa.size(); i++) it->second(sa[i]);
        }
    }
}


} // end of namespace pi

