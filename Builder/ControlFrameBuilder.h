//
// Created by ozanozbirecikli on 12/23/20.
//

#ifndef UNIX_SOCKET_CONTROLFRAMEBUILDER_H
#define UNIX_SOCKET_CONTROLFRAMEBUILDER_H


#include "FrameBuilder.h"

class ControlFrameBuilder : FrameBuilder {

private:

    MAC_Frame controlFrame;

public:

    ControlFrameBuilder() {

        controlFrame = ControlFrame();
    };

    void buildHeader(MAC_Header header) override {

        controlFrame.setHeader(header);
    };

    void buildBody(Frame_Body frameBody) override{

    };

    void setFCS(std::vector<uint8_t> FCS) override {

    };

    MAC_Frame build() override {
        return controlFrame;
    };


};


#endif //UNIX_SOCKET_CONTROLFRAMEBUILDER_H
