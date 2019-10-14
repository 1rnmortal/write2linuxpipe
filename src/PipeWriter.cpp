#include "PipeWriter.hpp"
#include <cstdlib>
#include <vector>
#include <cstring>
bool PipeWriter::SendMsg(std::string msg)
{

	if (nullptr == sendList)
	{
        std::cout<<"queue ptr is nullptr:"<<std::endl;
        return false;
    }
    auto list = split(msg.data(),";");
    for (auto item : list)
    {
        LogMsg temp;
        temp.size = item.size();
        if (temp.size >= BUF_SIZE)
        {
            std::cout<<"Glog error:msg is  too long:"<<temp.size<<" ";
            std::cout<<"content"<<item.data()<<std::endl;
            return false;
        }
        temp.content = item;
        sendList->push(temp);
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
        if (nullptr == sendList)
        {
            std::cout<<"queue ptr is nullptr:"<<std::endl;
            return;
        }
        while(sendList->size() != 0 )
        {
            LogMsg msg;
            if(!sendList->pop( msg))
                continue;
            int size = write(fd,msg.content.data(),msg.size);
            if (size <= 0)
            {
                std::cout<<"Glog error:wiret into pipe failed"<<std::endl;
                std::cout<<"content:"<<msg.content<<std::endl;
            }
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
