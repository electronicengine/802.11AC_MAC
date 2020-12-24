//
// Created by cenkerkaraors on 4.12.2020.
//
#include <stdint-gcc.h>

#ifndef FRAME_STRUCTURES_FRAMES_H
#define FRAME_STRUCTURES_FRAMES_H

#endif //FRAME_STRUCTURES_FRAMES_H
struct FrameControl
{
    uint8_t protocolVersion : 2;
    uint8_t type : 2;
    uint8_t subType : 4;
    uint8_t to_DS : 1;
    uint8_t from_DS : 1;
    uint8_t moreFragments : 1;
    uint8_t retry : 1;
    uint8_t powerManagement : 1;
    uint8_t moreData : 1;
    uint8_t protectedFrame : 1;
    uint8_t order : 1;
};

struct SequenceControl
{
    uint8_t fragmentNumber : 4;
    uint16_t sequenceNumber : 12;
};

struct HTControlMiddle {};

struct HT_Variant : HTControlMiddle
{
    uint16_t linkAdaptationControl : 15;
    uint8_t calibrationPosition : 2;
    uint8_t calibrationSequence : 2;
    uint8_t reserved : 2;
    uint8_t CSI_Steering : 2;
    uint8_t HTNDPAnnouncement : 1;
    uint8_t reserved_2 : 4;
    uint8_t dei : 1;

};

struct VHT_Variant : HTControlMiddle
{
    uint8_t reserved : 1;
    uint8_t mrq : 1;
    uint8_t msi_stbc : 3;
    uint8_t mfsi_gidl : 3;
    uint16_t MFB : 15;
    uint8_t gidh : 3;
    uint8_t codingType : 1;
    uint8_t FB_Tx_Type : 1;
    uint8_t unsolicitedMFB : 1;
};

struct HT_Control
{
    uint8_t VHT : 1;
    HTControlMiddle middle;
    uint8_t acConstraint : 1;
    uint8_t rdg_morePPDU : 1;
};

struct MAC_Header
{
    FrameControl frameControl;
    uint16_t duration_id[2];
    uint8_t address_1[6];
    uint8_t address_2[6];
    uint8_t address_3[6];
    SequenceControl sequenceControl;
    uint8_t address_4[6];
    uint16_t QoSControl;
    HT_Control htControl;
};

struct Frame_Body
{

};

struct MAC_Frame
{
    MAC_Header macHeader;
    Frame_Body frameBody;
    uint8_t FCS[4];

    void setHeader(MAC_Header header){ this->macHeader = header; }
    void setBody(Frame_Body body){ this->frameBody = body; }
//    void setFcs(std::vector<uint8_t> FCS){ vectorToArray(FCS, this->FCS); }

};

struct DataFrame:MAC_Frame
{
    MAC_Header header;
    Frame_Body body;
    uint8_t FCS[4];
};

struct ControlFrame:MAC_Frame
{
    MAC_Header header;
    uint8_t  FCS[4];
};

struct ManagementFrames:MAC_Frame
{
    MAC_Header header;
    Frame_Body body;
    uint8_t FCS[4];
};