
#include "utils_debug.h"


#ifdef _WIN32

int dbg_stacktrace_setup(void)
{
    fprintf(stderr, "ERR: your system do not support stack trace!\n");

    return -1;
}

#else // _WIN32

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>
#include <execinfo.h>
#include <errno.h>
#include <cxxabi.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <dirent.h>
#include <sys/wait.h>


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

pid_t popen2(const char *command, int *infp, int *outfp)
{
    #define READ    0
    #define WRITE   1

    int p_stdin[2], p_stdout[2];
    pid_t pid;

    if (pipe(p_stdin) != 0 || pipe(p_stdout) != 0)
        return -1;

    pid = fork();

    if (pid < 0)
        return pid;
    else if (pid == 0) {
        close(p_stdin[WRITE]);
        dup2(p_stdin[READ], READ);
        close(p_stdout[READ]);
        dup2(p_stdout[WRITE], WRITE);

        execl("/bin/sh", "sh", "-c", command, NULL);
        perror("execl");
        exit(1);
    }

    if (infp == NULL)
        close(p_stdin[WRITE]);
    else
        *infp = p_stdin[WRITE];

    if (outfp == NULL)
        close(p_stdout[READ]);
    else
        *outfp = p_stdout[READ];

    return pid;
}

int get_exec_output(char *cmd, char *buf, int buf_len)
{
    pid_t   pid;
    int     stat_loc;
    int     infp, outfp;
    int     i, l;
    ssize_t nread;

    // open pipe
    pid = popen2(cmd, &infp, &outfp);
    if ( pid <= 0) {
        printf("ERR: Unable to exec given program\n");
        exit(1);
    }

    // read output
    nread = read(outfp, buf, buf_len);

    // close pip file
    close(infp);
    close(outfp);

    // wait child process finished
    wait(&stat_loc);

    // process output buffer
    l = strlen(buf);

    // get first line
    for(i=0; i<l; i++) {
        if( buf[i] == '\n' || buf[i] == '\r' )
            buf[i] = '\0';
    }

    // normal method remove trailing \r
    /*
    if( buf[l-1] == '\n' || buf[l-1] == '\r' )
        buf[l-1] = '\0';
    */

    return 0;
}

static inline void printStackTrace( FILE *out = stderr, unsigned int max_frames = 100 )
{
    fprintf(out, "stack trace:\n");

    // storage array for stack trace address data
    void    *addrlist[max_frames+1];

    size_t  funcnamesize = 1024;
    char    funcname[1024];
    char    s_addr[200];
    char    s_off[200];
    char    s_cmd[1024];
    char    s_fileline[1024];

    unsigned int    i, j;

    // retrieve current stack addresses
    unsigned int addrlen = backtrace( addrlist, sizeof( addrlist ) / sizeof( void* ));

    if ( addrlen == 0 ) {
        fprintf( out, "  \n" );
        return;
    }

    // resolve addresses into strings containing "filename(function+address)",
    // Actually it will be ## program address function + offset
    // this array must be free()-ed
    char** symbollist = backtrace_symbols( addrlist, addrlen );

    for( i=0; i<addrlen-1; i++) {
        printf("addrlist[%3d]  0x%016zx\n", i, addrlist[i]);
    }

    for( i=0; i<addrlen-1; i++) {
        printf("symbolist[%3d] %s\n", i, symbollist[i]);
    }
    printf("\n");

    // iterate over the returned symbol lines. skip the first 3 line, last line
    //      it is the address of this function.
    for ( i = 3; i < addrlen-1; i++ ) {
        char* begin_name   = NULL;
        char* begin_offset = NULL;
        char* end_offset   = NULL;

        // find parentheses and +address offset surrounding the mangled name
#ifdef DARWIN
        // OSX style stack trace
        for ( char *p = symbollist[i]; *p; ++p ) {
            if (( *p == '_' ) && ( *(p-1) == ' ' ))
                begin_name = p-1;
            else if ( *p == '+' )
                begin_offset = p-1;
        }

        if ( begin_name && begin_offset && ( begin_name < begin_offset )) {
            *begin_name++ = '\0';
            *begin_offset++ = '\0';

            // mangled name is now in [begin_name, begin_offset) and caller
            // offset in [begin_offset, end_offset). now apply
            // __cxa_demangle():
            int status;
            char* ret = abi::__cxa_demangle( begin_name, &funcname[0],
                    &funcnamesize, &status );
            if ( status == 0 ) {
                funcname = ret; // use possibly realloc()-ed string
                fprintf( out, "  %-30s %-40s %s\n",
                         symbollist[i], funcname, begin_offset );
            } else {
                // demangling failed. Output function name as a C function with
                // no arguments.
                fprintf( out, "  %-30s %-38s() %s\n",
                         symbollist[i], begin_name, begin_offset );
            }

#else // !DARWIN - but is posix


        // not OSX style

        s_addr[0] = '\0';
        s_off[0]  = '\0';

        // ./module(function+0x15c) [0x8048a6d]
        for ( char *p = symbollist[i]; *p; ++p ) {
            if ( *p == '(' )
                begin_name = p;
            else if ( *p == '+' )
                begin_offset = p;
            else if ( *p == '[' && ( begin_offset || begin_name ) )
                end_offset = p;
        }

        // get address string
        if ( end_offset ) {
            for(char *p=end_offset, j=0; *p; ++p) {
                if( *p == '[' )
                    continue;
                else if( *p == ']' )
                    s_addr[j] = '\0';
                else
                    s_addr[j++] = *p;
            }
            //fprintf(out, "addr: %s\n", s_addr);
        }

        // get offset address
        if( begin_offset ) {
            for(char *p=begin_offset, j=0; *p; ++p) {
                if( *p == '+' )
                    continue;
                else if( *p == ')' ) {
                    s_off[j] = '\0';
                    break;
                } else
                    s_off[j++] = *p;
            }
            //fprintf(out, "offset: %s\n", s_off);
        }

        if ( begin_name && end_offset && ( begin_name < end_offset )) {
            *begin_name++   = '\0';
            *end_offset++   = '\0';

            if ( begin_offset )
                *begin_offset++ = '\0';

            // mangled name is now in [begin_name, begin_offset) and caller
            // offset in [begin_offset, end_offset). now apply
            // __cxa_demangle():

            int status = 0;
            char* ret = abi::__cxa_demangle( begin_name, funcname,
                                             &funcnamesize, &status );
            char* fname = begin_name;
            if ( status == 0 )
                fname = ret;

            if ( begin_offset ) {
                fprintf( out, "  %s [ \033[31m%s\033[0m + %s ] [%s]\n",
                         symbollist[i], fname, s_off, s_addr );
            } else {
                fprintf( out, "  %s [ %s   %s ] [%s]\n",
                         symbollist[i], fname, "", s_addr );
            }

            // print source file and line no.
            sprintf(s_cmd, "addr2line -e %s %s", symbollist[i], s_addr);
            printf(">> addr2line -e %s %s\n", symbollist[i], s_addr);

            get_exec_output(s_cmd, s_fileline, 1024);
            fprintf(out, "      \033[32m%s\033[0m\n", s_fileline);

#endif  // !DARWIN - but is posix
        } else {
            // couldn't parse the line? print the whole line.
            fprintf(out, "  %s\n", symbollist[i]);
        }
    }

    free(symbollist);
}

void abortHandler( int signum )
{
    // associate each signal with a signal name string.
    const char* name = NULL;

    // get signal name
    switch( signum )
    {
    case SIGABRT: name = "SIGABRT";  break;
    case SIGSEGV: name = "SIGSEGV";  break;
    case SIGBUS:  name = "SIGBUS";   break;
    case SIGILL:  name = "SIGILL";   break;
    case SIGFPE:  name = "SIGFPE";   break;
    }

    // notify the user which signal was caught. We use printf, because this is the most
    // basic output function. Once you get a crash, it is possible that more complex output
    // systems like streams and the like may be corrupted. So we make the most basic call
    // possible to the lowest level, most standard print function.
    printf("\n");
    printf("-------------------------------------------------------------------------------------------\n");
    if ( name )
        fprintf( stderr, "Caught signal %d (%s)\n", signum, name );
    else
        fprintf( stderr, "Caught signal %d\n", signum );

    // Dump a stack trace
    printStackTrace();

    printf("-------------------------------------------------------------------------------------------\n");

    // If you caught one of the above signals, it is likely you just
    // want to quit your program right now.
    exit( signum );
}


int dbg_stacktrace_setup(void)
{
    signal( SIGABRT, abortHandler );
    signal( SIGSEGV, abortHandler );
    signal( SIGBUS,  abortHandler );
    signal( SIGILL,  abortHandler );
    signal( SIGFPE,  abortHandler );
}

#endif // end of _WIN32

