#include "PipeWrapper.hpp"
#include <cstdio>
#include <string>
#include <iostream>
namespace PipeLibWrapper
{
    PipeWriter pObj ;
    bool  writeIntoPipe(char* msg)
    {
        std::string str = msg;
        return pObj.SendMsg(str);
    }
    bool  initPipe(char* path)
    {
        std::cout<< "Glog path" << path<<std::endl;
        return pObj.init(path);
    }

}
