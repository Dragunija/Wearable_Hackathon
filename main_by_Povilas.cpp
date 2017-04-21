#include "mbed.h"

#include "ReceiverIR.h"
#include "TransmitterIR.h"
#include "beep.h"



Serial pc(USBTX, USBRX);
ReceiverIR ir_rx(p15);
TransmitterIR ir_tx(p21);
Beep buzz(p12);
DigitalOut led1(LED1);

PwmOut led(LED1);

//DigitalOut leds[4] = {(LED1), (LED2), (LED3), (LED4)};


// main() runs in its own thread in the OS
int main() {
    int lives = 1;
    int player_id = 1; //hardcoded
    int nmOOtherPlayers = 1;
    int otherIDs[nmOOtherPlayers];
    otherIDs[0] = 2;
    /*
    for(int i=1; i<nmOOtherPlayers; i++) {
        otherIDs[i] = {2};
    }
    */
    int state = 1; // 1 = alive, 0 = dead

    
    

    
    
    while (true) {
        
        //Receiving
        RemoteIR::Format format;
        uint8_t buf[32];
        int bitcount=0;
        if (ir_rx.getState() == ReceiverIR::Received) {
            bitcount = ir_rx.getData(&format, buf, sizeof(buf) * 8);
        }
        
        //
        //probably susebtable to noise
        for(int i=0; i<nmOOtherPlayers; i++) {
            if(bitcount!=otherIDs[i]) {
                lives--;
            }
        }
        
        if(lives<=0) {
            state = 0;
        }
        
        if (state!=0) {
        //Transmitting
            RemoteIR::Format format = RemoteIR::SONY;
            uint8_t buf[] = { 0x80, 0x00 };
            int bitcount = player_id;
            if (ir_tx.getState() == TransmitterIR::Idle) {
                bitcount = ir_tx.setData(format, buf, bitcount);
            }
        }
        
        if (state == 0) {
            buzz.beep(500, 2);
            led1=1;
        }
        
    }
}


// Abilities:
// 
