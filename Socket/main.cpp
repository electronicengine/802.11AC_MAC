#include "connection.h"
#include "../Builder/ControlFrameBuilder.h"
#include "../Frames/ControlFrames.h"

int main() {
    auto conn = Connection(false, Logging::cyan);
    conn.operate();
    ControlFrameBuilder builder = ControlFrameBuilder();
    RTS rts = RTS();
    builder.buildHeader(rts);
    std::vector<uint8_t> FCS = {1,2};
    builder.setFCS(FCS);

    return 0;
}
