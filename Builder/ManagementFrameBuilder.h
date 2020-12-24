//
// Created by ozanozbirecikli on 12/23/20.
//

#ifndef UNIX_SOCKET_MANAGEMENTFRAMEBUILDER_H
#define UNIX_SOCKET_MANAGEMENTFRAMEBUILDER_H


#include "FrameBuilder.h"

class ManagementFrameBuilder : FrameBuilder {

private:

    MAC_Frame managementFrame;

public:

    ManagementFrameBuilder() {
        managementFrame = ManagementFrame();
    };

    void buildHeader(MAC_Header header) override {
        managementFrame.setHeader(header);
    };


    void buildBody(Frame_Body frameBody) override {
        managementFrame.setBody(frameBody);
    };

    void setFCS(std::vector<uint8_t> FCS) override {

    };

    MAC_Frame build() override {
        return &managementFrame;
    };

};


#endif //UNIX_SOCKET_MANAGEMENTFRAMEBUILDER_H
