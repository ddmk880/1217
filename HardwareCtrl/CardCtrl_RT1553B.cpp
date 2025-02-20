#include "CardCtrl_RT1553B.h"
#include<iostream>
#include<stdio.h>


CardCtrl_RT1553B::CardCtrl_RT1553B()
{


}

CardCtrl_RT1553B::~CardCtrl_RT1553B()
{

}

void CardCtrl_RT1553B::Init_RT1553Card()
{

    BT_INT status;
    BT_UINT ch_id;
    API_RT_ABUF Abuf_RT1; // RT address buffer structure.
    API_RT_CBUF Cbuf_RT1SA1R, Cbuf_RT1SA2T; // RT control buffer structures.
    API_RT_MBUF_WRITE msg_buffer_write;
    API_RT_MBUF_READ msg_buffer_read;
    char c;
    unsigned short cmd, sts;
    int i ,dev_num, mode;
    //-------------------------- Initialize API and board -----------------------------
    // First find the device based on type and instance.
    dev_num = BusTools_FindDevice(CPCI1553, 1);
    if (dev_num < 0) {return;}
    // Open the device and get the channel id.
    mode = API_B_MODE | API_SW_INTERRUPT; // 1553B protocol, use SW interrupts.
    status = BusTools_API_OpenChannel( &ch_id, mode, dev_num, CHANNEL_1);
    if (status == API_SUCCESS)
    {
    // Select External Bus.
    status = BusTools_SetInternalBus(ch_id, 0);
    if (status != API_SUCCESS) {return;}
    // Now lets set up an RT.
    status = BusTools_RT_Init(ch_id, 0);
    if (status == API_SUCCESS)
    {
    // Setup RT address buffer for our RT (RT1)
    Abuf_RT1.enable_a = 1; // Respond on bus A
    Abuf_RT1.enable_b = 1; // Respond on bus B
    Abuf_RT1.inhibit_term_flag = 1; // Inhibit terminal flag in status word
    Abuf_RT1.status = 0x0800; // Set status word
    Abuf_RT1.bit_word = 0x0000; // Set BIT word (for mode code 19)
    status = BusTools_RT_AbufWrite(ch_id, 1, &Abuf_RT1);
    if (status != API_SUCCESS) {return;}
    // Setup a control buffer - RT1, SA1, Receive, 1 buffer.
    Cbuf_RT1SA1R.legal_wordcount = 0xFFFFFFFF; // any word count is legal.
    status = BusTools_RT_CbufWrite(ch_id, 1, 1, 0, 1, &Cbuf_RT1SA1R);
    if (status != API_SUCCESS) {return;}
    // Setup a control buffer - RT1, SA2, Transmit, 1 buffer.
    Cbuf_RT1SA2T.legal_wordcount = 0xFFFFFFFF; // any word count is legal.
    status = BusTools_RT_CbufWrite(ch_id, 1, 2, 1, 1, &Cbuf_RT1SA2T);
    if (status != API_SUCCESS) {return;}
    // Put some data in our transmit buffer
    msg_buffer_write.enable = 0; // No interrupts enabled
    msg_buffer_write.error_inj_id = 0; // No error injection
    for (i=0; i<32; i++)
    msg_buffer_write.mess_data[i] = 0xAB00 + i;
    status = BusTools_RT_MessageWrite(ch_id, 1, 2, 1, 0, &msg_buffer_write);
    if (status != API_SUCCESS) {return;}
    // Now lets turn on our RT
    status = BusTools_RT_StartStop(ch_id, 1);
    if (status != API_SUCCESS) {return;}
    do {
    printf("\nInput Q to stop RT and exit, anything else to read RT1 SA1 RCV data buffer.\n");
    scanf("%c",&c);
    if (c != 'Q')
    {
    // Read the data buffer
    status=BusTools_RT_MessageRead(ch_id,1, 1, 0, 0, &msg_buffer_read);
    }
    } while (c != 'Q'); // End of do-while
    //Stopping RT simulation
    status = BusTools_RT_StartStop(ch_id, 0);
    if (status != API_SUCCESS) {return;}
    }
    // Close API and board
    status = BusTools_API_Close(ch_id);
    }

    return ;
}
