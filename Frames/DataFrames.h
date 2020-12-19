//
// Created by cenkerkaraors on 5.12.2020.
//
#include "frames.h"
#ifndef FRAME_STRUCTURES_DATA_FRAMES_H
#define FRAME_STRUCTURES_DATA_FRAMES_H

#endif //FRAME_STRUCTURES_DATA_FRAMES_H

struct A_MSDU : Frame_Body
{
    uint8_t DA[6];
    uint8_t SA[6];
    uint8_t length[2];
    uint8_t * MSDU;
    uint8_t padding[3];
};