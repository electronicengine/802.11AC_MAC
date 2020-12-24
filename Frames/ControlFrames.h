//
// Created by OZAN on 5.12.2020.
//

#ifndef INC_802_11AC_MAC_CONTROLFRAMES_H
#define INC_802_11AC_MAC_CONTROLFRAMES_H


struct RTS : MAC_Header {
   
  FrameControl frameControl;
    uint8_t Duration[2];
    uint8_t RA[6];
    uint8_t TA[6];
};

struct CTS : MAC_Header {

    FrameControl FrameControl;
    uint8_t Duration[2];
    uint8_t RA[6];
};

struct ACK : MAC_Header {

    FrameControl FrameControl;
    uint8_t Duration[2];
    uint8_t RA[6];
};

struct PS_Poll : MAC_Header {

    FrameControl FrameControl;
    uint8_t AID[2];
    uint8_t BSSID[6];
    uint8_t RA[6];
};

struct CF_END : MAC_Header {

    FrameControl FrameControl;

    uint8_t Duration[2];
    uint8_t RA[6];
    uint8_t BSSID[6];
};

struct CF_END_CF_ACK : MAC_Header {

    FrameControl FrameControl;
    uint8_t Duration[2];
    uint8_t RA[6];
    uint8_t BSSID[6];
};

struct BlockackAckReq {

    FrameControl FrameControl;
    uint8_t Duration_ID[2];
    uint8_t RA[6];
    uint8_t TA[6];

};

struct BarControl {
    uint8_t BAR_Ack_Policiy:1;
    uint8_t Multi_TID:1;
    uint8_t Compressed_Bitmap:1;
    uint8_t Reserved:9;
    uint8_t TID_INFO:4;
};


struct BlockAckReqFrame {
    BlockackAckReq MAC_Header;
    BarControl Bar_Control;
    uint8_t BarInformation;
    uint8_t FCS[4];
};


struct ControlWrapper {
    FrameControl frameControl;
    uint8_t Duration_ID[2];
    uint8_t Address1[6];
    uint8_t Carried_Frame_Control[2];
    uint8_t HT_Control[4];
    uint8_t CarriedFrame;
    uint8_t FCS[4];
};

struct Sounding_Dialog_Token {
    uint8_t Reserved:2;
    uint8_t Sounding_Dialog_Token_Number:6;
};

struct STA_Info1 {
    uint8_t AID12 :12;
    uint8_t FeedbackType:1;
    uint8_t NcIndex:3;

};

struct VHT_NDP {
    
  FrameControl frameControl;
    uint8_t Duration[2];
    uint8_t RA[6];
    uint8_t TA[6];
    Sounding_Dialog_Token SoundingDialogToken;
    STA_Info1 STAInfo1[2];
    uint8_t STAInfo_n[2];
    uint8_t FCS[4];

};


struct BeamformingReportPool {
  
    FrameControl frameControl;
    uint8_t Duration[2];
    uint8_t RA[6];
    uint8_t TA[6];
    uint8_t Feedback_Segment_Retransmission_Bitmap[6];
    uint8_t FCS[4];
};

#endif //INC_802_11AC_MAC_CONTROLFRAMES_H
