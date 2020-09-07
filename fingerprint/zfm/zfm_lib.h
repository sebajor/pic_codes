/* The data package has the format:
 * head:    2bytes -->EF01H
 * Adder:   4bytes -->0xFFFFFFFF
 * PID:     1bytes --> comm, data, ack, end_pack
 * len:     2bytes
 * data:    ----
 * checksum: pid+len+data 
 * 
 * we only make the constant size data commands. because its easier
 */

#ifndef __ZFM_CTE__
#define __ZFM_CTE__

#define ZFM_HEAD 0xEF01
#define ZFM_ADDR 0xFFFFFFFF    

//PID
#define ZFM_COM_PID 0X1
#define ZFM_DAT_PID 0X2
#define ZFM_ACK_PID 0X7
#define ZFM_END_PID 0X8

//confirmation codes
#define ZFM_complete_code 0x00
#define ZFM_no_finger_code 0X02
#define ZFM_error_enroll_code 0x03
#define ZFM_no_match_code 0x08
#define ZFM_no_found_code 0x09
#define ZFM_error_del_code 0x10
#define ZFM_fail_clear_code 0x11
#define ZFM_addr_error_code 0x20
#define ZFM_first_acq_code 0x56
#define ZFM_sec_acq_code 0x57
#define ZFM_repited_enroll_code 0x24


//command definitions
static unsigned char _zfm_det_finger[6] = {ZFM_COM_PID,0x0,0x3,0x1,0x00,0x5}; //detects a finger
static unsigned char _zfm_light_on[6] = {ZFM_COM_PID,0x00,0x03,0x50,0x00,0x54}; //turn light on
static unsigned char _zfm_light_off[6] ={ZFM_COM_PID,0x0,0x03,0x51,0x00,0x55};  //turn light off
static unsigned char _zfm_capt_finger[6] = {ZFM_COM_PID,0x0,0x03,0x52,0x0, 0x56}; // captures a finger
                                                                                //needs the light on
static unsigned char _zfm_handshake[6] = {ZFM_COM_PID,0x0,0x03,0x53,0x0,0x57}; //to check the state
//static unsigned char zfm_autoenroll[]
//static unsigned char zfm_autosearch[]

static unsigned char _zfm_gen_chars1[7] = {ZFM_COM_PID,0x0,0x4,0x2,0x1,0x0,0x8}; //generate characts and 
                                                                                //saves in buffer1 
static unsigned char _zfm_gen_chars2[7] = {ZFM_COM_PID,0x0,0x4,0x2,0x2,0x0,0x9}; //generate characts and
                                                                                //saves in buffer2
//static unsigned char zfm_upload_char1[6]
//static unsigned char zfm_upload_char2[6]
//static unsigned char zfm_download_char1[6]
//static unsigned char zfm_download_char2[6]

//carefull with the next ones....
static unsigned char _zfm_store_char[4] = {ZFM_COM_PID,0x0,0x6,0x6}; 
                        //saves the data in buffer1 in flash, the last 5 bytes correspond to
                        //bufferID(1Bytes), PageID(2Byte), Checksum(2Bytes).. Those values
                        //has to be set by the user


static unsigned char _zfm_delete[4] = {ZFM_COM_PID,0x0,0x7,0x0c};
static unsigned char _zfm_search[4] = {ZFM_COM_PID, 0x0,0x8,0x4};

static unsigned char _zfm_delete_all[6] = {ZFM_COM_PID,0x0,0x3,0xd,0x0,0x11};  
static unsigned char _zfm_compare[6] = {ZFM_COM_PID, 0x0,0x3,0x3,0x0,0x7};



#endif

