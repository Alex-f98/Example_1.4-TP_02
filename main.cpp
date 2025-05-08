#include "mbed.h"
#include "arm_book_lib.h"


#define CODE  0b1100

#define ONLY_BUSIN

#ifdef ONLY_BUSIN

int main()
{
    //BusIn permite agregar multiples pines(de cualquier port) de entrada a un solo objeto y poder leerlos en simultaneo (en la lectura es bloqueante pero no tarda nada)
    //Port in es lo mismo pero mas eficiente ya que esta optimizado para tratabar con los registros del micro directamente(accede a un puerto directamente).
    
    //Sensores
    DigitalIn gasDetector(D2);
    DigitalIn overTempDetector(D3);
    //Teclas de codigo
    //DigitalIn aButton(D4);
    //DigitalIn bButton(D5);
    //DigitalIn cButton(D6);
    //DigitalIn dButton(D7);
    //https://github.com/ARMmbed/mbed-os/blob/d723bf9e55415433e108124ee6d36337feddf1b8/drivers/include/drivers/BusIn.h#L36
    //Internamente es un port en los argumentos y les asigna un digitalIn
    BusIn codeButtons(D4, D5, D6, D7); //0000 0000 0000 D4.D5.D6.D7

    DigitalOut alarmLed(LED1);

    gasDetector.mode(PullDown);
    overTempDetector.mode(PullDown);
    //aButton.mode(PullDown);
    //bButton.mode(PullDown);
    //cButton.mode(PullDown);
    //dButton.mode(PullDown);
    for (int i=0; i<4; i++){
        codeButtons[i].mode(PullDown);
    }

    alarmLed = OFF;

    bool alarmState = OFF;

    while (true) {

        if ( gasDetector || overTempDetector ) {
            alarmState = ON;
        }

        alarmLed = alarmState;

        //codigo [a, b, c, d]<-[1, 1, 0, 0]
        if (codeButtons.read() == CODE) {
            alarmState = OFF;
        }
    }
}

#else

int main()
{
    //BusIn permite agregar multiples pines(de cualquier port) de entrada a un solo objeto y poder leerlos en simultaneo (en la lectura es bloqueante pero no tarda nada)
    //Port in es lo mismo pero mas eficiente ya que esta optimizado para tratabar con los registros del micro directamente(accede a un puerto directamente).
    
    //Sensores
    DigitalIn gasDetector(D2);
    DigitalIn overTempDetector(D3);

    //Teclas de codigo
    //https://github.com/ARMmbed/mbed-os/blob/d723bf9e55415433e108124ee6d36337feddf1b8/drivers/include/drivers/PortIn.h#L58
    //0000 0000  D4.D5.D6.D7 0000
    //Bit:     7 6 5 4 _ 3 2 1 0
    //Mask:    1 1 1 1 _ 0 0 0 0  ← 0xF0 = 11110000

    PortIn codeButtons(portA, 0xF0);

    DigitalOut alarmLed(LED1);

    gasDetector.mode(PullDown);
    overTempDetector.mode(PullDown);

    codeButtons.mode(PullDown);

    alarmLed = OFF;

    bool alarmState = OFF;

    while (true) {

        if ( gasDetector || overTempDetector ) {
            alarmState = ON;
        }

        alarmLed = alarmState;

        //codigo [a, b, c, d]<-[1, 1, 0, 0]
        if ((codeButtons.read()>>4) == CODE) { // o cambiar el codigo a 0b1100 0000
            alarmState = OFF;
        }
    }
}

#endif