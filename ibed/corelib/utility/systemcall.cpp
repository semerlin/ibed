#include "systemcall.h"
#include <QString>

#ifdef Q_OS_LINUX
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define SHELL "/bin/sh"

#define USE_USEDEFINE

#ifndef USE_USEDEFINE
    #define SYSTEM system
    #define POPEN popen
    #define PCLOSE pclose
#else
    #define SYSTEM system_user
    #define POPEN popen_user
    #define PCLOSE pclose_user
#endif

/**
 * @brief user define system function.use vfork instead of fork
 * @param
 * @return
 */
static int system_user(const char *cmdstring)
{
    pid_t pid;
    int status;

    if(cmdstring == NULL)
        return (1);

    if((pid = vfork())<0)
        status = -1;
    else if(pid == 0)
    {
        execl(SHELL, "sh", "-c", cmdstring, (char *)0);
        _exit(127);
    }
    else
    {
        while(waitpid(pid, &status, 0) < 0)
        {
            if(errno != EINTR)
            {
                status = -1;
                break;
            }
        }
    }

    return status;
}


static pid_t *childpid = NULL;  /* ptr to array allocated at run-time */
static int maxfd;  /* from our open_max(), {Prog openmax} */
/**
 * @brief popen_user user defined popen
 * @param cmdstring command that need to excuted
 * @param type r: read
 *             w: write
 * @return return file handle if open success, otherwise return NULL
 */
static FILE* popen_user(const char *cmdstring, const char *type)
{
    int i, pfd[2];
    pid_t pid;
    FILE *fp;

    /* only allow "r" or "w" */
    if ((type[0] != 'r' && type[0] != 'w') || type[1] != 0)
    {
        errno = EINVAL;     /* required by POSIX.2 */
        return(NULL);
    }

    if(childpid == NULL)
    {
        /* first time through */
        /* allocate zeroed out array for child pids */
        maxfd = FOPEN_MAX;//open_max();
        if((childpid = (pid_t *)calloc(maxfd, sizeof(pid_t))) == NULL)
            return(NULL);
    }

    if (pipe(pfd) < 0)
        return(NULL);   /* errno set by pipe() */

    if ((pid = vfork()) < 0)
        return(NULL);   /* errno set by vfork() */
    else if (pid == 0)
    {
        /* child */
        if (*type == 'r')
        {
            close(pfd[0]);
            if (pfd[1] != STDOUT_FILENO)
            {
                dup2(pfd[1], STDOUT_FILENO);
                close(pfd[1]);
            }
        }
        else
        {
            close(pfd[1]);
            if (pfd[0] != STDIN_FILENO)
            {
                dup2(pfd[0], STDIN_FILENO);
                close(pfd[0]);
            }
        }
        /* close all descriptors in childpid[] */
        for (i = 0; i < maxfd; i++)
            if (childpid[ i ] > 0)
                close(i);

        execl(SHELL, "sh", "-c", cmdstring, (char *) 0);
        _exit(127);
    }
                                /* parent */
    if (*type == 'r')
    {
        close(pfd[1]);
        if((fp = fdopen(pfd[0], type)) == NULL)
            return(NULL);
    }
    else
    {
        close(pfd[0]);
        if((fp = fdopen(pfd[1], type)) == NULL)
            return(NULL);
    }

    childpid[fileno(fp)] = pid; /* remember child pid for this fd */
    return(fp);
}

/**
 * @brief used with pclose_user
 * @param fp: file handle that return by popen_user
 * @return return 0 if close success, otherwise return none zero
 */
static int pclose_user(FILE *fp)
{
    int fd, stat;
    pid_t pid;

    if(childpid == NULL)
        return(-1);     /* popen() has never been called */

    fd = fileno(fp);
    if((pid = childpid[fd]) == 0)
        return(-1);     /* fp wasn't opened by popen() */

    childpid[fd] = 0;
    if(fclose(fp) == EOF)
        return(-1);

    while(waitpid(pid, &stat, 0) < 0)
        if (errno != EINTR)
            return(-1); /* error other than EINTR from waitpid() */

    return(stat);   /* return child's termination status */
}

#endif


SystemCall::SystemCall()
{

}

/**
 * @brief return SystemCall reference
 * @return
 */
SystemCall &SystemCall::instance()
{
    static SystemCall m_sysCall;
    return m_sysCall;
}

/**
 * @brief run system command and return command excute information
 * @param command string
 * @param return infomation after run this command string
 * @return return 0 if success, otherwise none zero
 */
int SystemCall::cmd(const QString &cmd, QString &outinfo)
{
#ifdef Q_OS_LINUX
    char buf[18];
    memset(buf, '\0', sizeof(buf));
    FILE *stream;
    stream = POPEN(cmd.toLatin1().constData(), "r");
    if(stream)
    {
        unsigned char retLen = fread(buf, 1, 16, stream);
        while(retLen != 0)
        {
            buf[retLen] = '\0';
            outinfo += buf;
            retLen = fread(buf, 1, 16, stream);
        }

        return PCLOSE(stream);
    }

    return (-1);
#endif
}

/**
 * @brief excute command
 * @param cmd: command need to excute
 * @return -1 ,127 indicates failed
 */
int SystemCall::cmd(const QString &cmd)
{
#ifdef Q_OS_LINUX
    return SYSTEM(cmd.toLatin1().constData());
#endif
}
