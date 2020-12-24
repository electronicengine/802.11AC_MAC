//
// Created by ozanozbirecikli on 12/23/20.
//

#ifndef UNIX_SOCKET_FRAMEBUILDER_H
#define UNIX_SOCKET_FRAMEBUILDER_H

#include "../Frames/frames.h"

class FrameBuilder{

private:



public:


    FrameBuilder(){


    }

    virtual void buildHeader(MAC_Header header) = 0;
    virtual void buildBody(Frame_Body frameBody) = 0;
    virtual void setFCS(std::vector<uint8_t> FCS) = 0;
    virtual MAC_Frame build() = 0;

};


#endif //UNIX_SOCKET_FRAMEBUILDER_H
