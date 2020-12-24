//
// Created by ozanozbirecikli on 12/23/20.
//

#ifndef UNIX_SOCKET_DATAFRAMEBUILDER_H
#define UNIX_SOCKET_DATAFRAMEBUILDER_H


#include "FrameBuilder.h"

class DataFrameBuilder : FrameBuilder {

private:

    MAC_Frame dataFrame;

public:

    DataFrameBuilder() {
        dataFrame = DataFrame();
    };

    void buildHeader(MAC_Header header) override {
        dataFrame.setHeader(header);
    };

    void buildBody(Frame_Body frameBody) override {
        dataFrame.setBody(frameBody);
    };

    void setFCS(std::vector<uint8_t> FCS) override {

    };

    MAC_Frame build() override {
        return &dataFrame;
    };

};


#endif //UNIX_SOCKET_DATAFRAMEBUILDER_H
