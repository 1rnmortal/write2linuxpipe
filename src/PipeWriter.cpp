#include "PipeWriter.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>
 bool PipeWriter::SendMsg(char* msg)
{
    auto list = split(msg,";");
    for (auto item : list)
    {
        LogMsg temp;
        temp.size = strlen(item.data())+1;
        if (temp.size >= BUF_SIZE)
        {
            std::cout<<"Glog error:msg is  too long:"<<temp.size<<std::endl;
	        std::cout<<"content"<<item.data()<<std::endl;
            return false;
        }
        strncpy(temp.content,item.data(),temp.size);
        sendList.push(temp);
    }
    return true;
}


bool PipeWriter::init(char* path)
{

    if(access(path,0)!= 0)
    {
        if ((mkfifo(path, O_CREAT | O_EXCL |O_RDWR) < 0) && (errno != EEXIST))
        {
            perror("can not creat fifoserver");
            exit(1);
        }
    }
    fd = open(path, O_WRONLY | O_NONBLOCK,0);
    if (fd == -1)
    {
        perror("open error;no reading process");
        exit(1);
    }
    std::thread td(&PipeWriter::WriteLoop,this);
    td.detach();
    return true;
}
void PipeWriter::WriteLoop()
{
    while(1)
    {
        while(!sendList.empty())
        {
            LogMsg msg = sendList.front();
            int size = write(fd,msg.content,msg.size);
            if (size <= 0)
            {
                std::cout<<"Glog error:wiret into pipe failed"<<std::endl;
                std::cout<<"content:"<<msg.content<<std::endl;
            }
            sendList.pop();
        }
       usleep(50*1000);
    }
}

std::vector<std::string> split(const char *s, const char *delim)
{
    std::vector<std::string> result;
    if (s && strlen(s))
    {
        int len = strlen(s);
        char *src = new char[len + 1];
        strcpy(src, s);
        src[len] = '\0';
        char *tokenptr = strtok(src, delim);
        while (tokenptr != NULL)
        {
            std::string tk = tokenptr;
            result.emplace_back(tk);
            tokenptr = strtok(NULL, delim);
        }
        delete[] src;
    }
    return result;
}
