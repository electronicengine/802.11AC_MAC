//
// Created by cenkerkaraors on 5.12.2020.
//
#include "frames.h"
#ifndef FRAME_STRUCTURES_MANAGEMENT_FRAMES_H
#define FRAME_STRUCTURES_MANAGEMENT_FRAMES_H

#endif //FRAME_STRUCTURES_MANAGEMENT_FRAMES_H

// Management Frames
struct ManagementHeader : MAC_Header
{
    FrameControl frameControl;
    uint16_t duration_id[2];
    uint8_t address_1[6];
    uint8_t address_2[6];
    uint8_t address_3[6];
    SequenceControl sequenceControl;
    HT_Control htControl;
};

struct ActionField
{
    uint8_t category;
    uint8_t * actionDetails;
};

struct SSID
{
    uint8_t elementID;
    uint8_t length;
    uint8_t ssid[32]; // 0-32
};

struct SupportedRates
{
    uint8_t elementID;
    uint8_t length;
    uint8_t supportedRates[8]; // 1-8
};

struct Beacon : Frame_Body
{
    uint8_t timestamp[8];
    uint16_t beaconInterval;
    uint16_t capability;
    SSID ssid;
    SupportedRates supportedRates;
};

struct ATIM : Frame_Body
{
    // Body is NULL;
};

struct Disassociation : Frame_Body
{
    uint16_t reasonCode;
    uint8_t last_1;
    uint8_t MME;
};

struct AssociationRequest : Frame_Body
{
    uint16_t capability;
    uint16_t listenInterval;
    SSID ssid;
    SupportedRates supportedRates;
};

struct AssociationResponse : Frame_Body
{
    uint16_t capability;
    uint16_t statusCode;
    uint16_t AID;
    SupportedRates supportedRates;
    uint8_t EDCAParamSet[20];

};

struct ReassociationRequest : Frame_Body
{
    uint16_t capability;
    uint16_t listenInterval;
    uint8_t currentAPAddress[6];
    SSID ssid;
    SupportedRates supportedRates;
};

struct ReassociationResponse : Frame_Body
{
    uint16_t capability;
    uint16_t statusCode;
    uint16_t AID;
    SupportedRates supportedRates;
    uint8_t EDCAParamSet[20];
};

struct ProbeRequest : Frame_Body
{
    SSID ssid;
    SupportedRates supportedRates;
};

struct ProbeResponse : Frame_Body
{
    uint8_t timestamp[8];
    uint16_t beaconInterval;
    uint16_t capability;
    SSID ssid;
    SupportedRates supportedRates;
};

struct Authentication : Frame_Body
{
    uint16_t authAlgNumber;
    uint16_t authTransactionSeqNumber;
    uint16_t statusCode;
};

struct Deuthentication : Frame_Body
{
    uint16_t reasonCode;
    uint8_t * last_1;
    uint8_t * MME;
};

struct Action : Frame_Body
{
    ActionField action;
    uint8_t * last_1;
    uint8_t * MME;
};

struct Action_No_ACK : Frame_Body
{
    ActionField action;
    uint8_t * last;
};

struct TimingAdvertisement : Frame_Body
{
    uint8_t timestamp[8];
    uint16_t capability;
};
