#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<iostream>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<queue>
#include<thread>
#include "lockFreeQueue.h"
#define BUF_SIZE 512
struct LogMsg
{
    LogMsg()
    {
        clear();
    }
    std::string content;
    int size;
    void clear()
    {
        content.clear();
        size = 0;
    }
};
class PipeWriter
{
    private:
        char* _path;
        void WriteLoop();
        int fd ;
        LockFreeQueueCpp11<LogMsg>* sendList;
    public:
        PipeWriter()
        {
            sendList = new LockFreeQueueCpp11<LogMsg>(16);
        }
        ~PipeWriter()
        {
            delete sendList;
        }
        bool SendMsg(std::string msg);
        bool init(char* path) ;
};
std::vector<std::string> split(const char *s, const char *delim);
