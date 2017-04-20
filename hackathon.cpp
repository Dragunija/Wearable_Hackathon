
#include "mbed.h"
#include "beep.h"

Serial pc(USBIX,USBRX);
Serial infrared(p, p);
Serial rf(p);
Beep buzz(p);


int main(){
    
int death_timer = 15;
float firing_signal=;
float bomb_signal=;

while (1){
    rf.putc(id);
    infrared.putc(firing_signal);
    if(infrared.readable()==firing_signal){
        buzz();
    }
    if(rf.readable()==bomb_signal){
        timer++;
        if (timer>death_timer){
            buzz();
        }
    }
    }
}
