#include "mbed.h"
#include "arm_book_lib.h"

int main()
{
    //Sensores
    DigitalIn gasDetector(D2);
    DigitalIn overTempDetector(D3);
    //Teclas de codigo
    DigitalIn aButton(D4);
    DigitalIn bButton(D5);
    DigitalIn cButton(D6);
    DigitalIn dButton(D7);

    DigitalOut alarmLed(LED1);

    gasDetector.mode(PullDown);
    overTempDetector.mode(PullDown);
    aButton.mode(PullDown);
    bButton.mode(PullDown);
    cButton.mode(PullDown);
    dButton.mode(PullDown);

    alarmLed = OFF;

    bool alarmState = OFF;

    while (true) {

        if ( gasDetector || overTempDetector ) {
            alarmState = ON;
        }

        alarmLed = alarmState;

        //codigo [a, b, c, d]<-[1, 1, 0, 0]
        if ( aButton && bButton && !cButton && !dButton) {
            alarmState = OFF;
        }
    }
}