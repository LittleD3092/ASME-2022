//Button
#define BUTTON_VALVE_OPEN 4
#define BUTTON_VALVE_CLOSE 5
#define BUTTON_CAR_LEFT 6
#define BUTTON_CAR_RIGHT 7
#define BUTTON_CAR_FRONT 8
#define BUTTON_CAR_BRAKE 9

bool button_state[2] = {0};

//nRF24L01
#include <SPI.h>
#include "RF24.h"

#define NRF24L01_CE 2
#define NRF24L01_CSN 3
#define NRF24L01_CHANNEL 83             //0-125, 2400MHz + CHANNEL
#define NRF24L01_PA_LEVEL RF24_PA_LOW   //RF24_PA_MIN 
                                        //RF24_PA_LOW
                                        //RF24_PA_HIGH
                                        //RF24_PA_MAX
#define NRF24L01_DATA_RATE RF24_1MBPS   //RF24_250KBPS
                                        //RF24_1MBPS
                                        //RF24_2MBPS

RF24 radio(NRF24L01_CE, NRF24L01_CSN);

const byte addr[] = "1Node";

void setup()
{
    //Button
    pinMode(BUTTON_VALVE_OPEN, INPUT);
    pinMode(BUTTON_VALVE_CLOSE, INPUT);
    pinMode(BUTTON_CAR_LEFT, INPUT);
    pinMode(BUTTON_CAR_RIGHT, INPUT);
    pinMode(BUTTON_CAR_FRONT, INPUT);
    pinMode(BUTTON_CAR_BRAKE, INPUT);

    //nRF24L01
    radio.begin();
    radio.setChannel(NRF24L01_CHANNEL);
    radio.openWritingPipe(addr);
    radio.setPALevel(NRF24L01_PA_LEVEL);
    radio.setDataRate(NRF24L01_DATA_RATE);
    radio.stopListening();
}

void loop()
{
    if(digitalRead(BUTTON_VALVE_OPEN) == HIGH && button_state[0] == false)      //button pressed
    {
        button_state[0] = true;
        const char msg[] = "open valve";
        radio.write(&msg, sizeof(msg));
    }
    else if(digitalRead(BUTTON_VALVE_OPEN) == LOW && button_state[0] == true)   //button released
    {
        button_state[0] = false;
        const char msg[] = "valve stop";
        radio.write(&msg, sizeof(msg));
    }

    if(digitalRead(BUTTON_VALVE_CLOSE) == HIGH && button_state[1] == false)
    {
        button_state[1] = true;
        const char msg[] = "close valve";
        radio.write(&msg, sizeof(msg));
    }
    else if(digitalRead(BUTTON_VALVE_CLOSE) == LOW && button_state[1] == true)
    {
        button_state[1] = false;
        const char msg[] = "valve stop";
        radio.write(&msg, sizeof(msg));
    }

    if(digitalRead(BUTTON_CAR_LEFT) == HIGH)
    {
        const char msg[] = "car left";
        radio.write(&msg, sizeof(msg));
    }
    else if(digitalRead(BUTTON_CAR_RIGHT) == HIGH)
    {
        const char msg[] = "car right";
        radio.write(&msg, sizeof(msg));
    }
    else if(digitalRead(BUTTON_CAR_FRONT) == HIGH)
    {
        const char msg[] = "car foward";
        radio.write(&msg, sizeof(msg));
    }
    else if(digitalRead(BUTTON_CAR_BRAKE) == HIGH)
    {
        const char msg[] = "car brake";
        radio.write(&msg, sizeof(msg));
    }

    delay(100);
}
