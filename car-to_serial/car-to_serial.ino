//water valve
// #define WATER_VALVE_TT_MOTOR_IN1 2
// #define WATER_VALVE_TT_MOTOR_IN2 4

//turning
// #include <Servo.h>
// Servo turning_servo;

// #define TURNING_SERVO_LEFT_ANGLE 0
// #define TURNING_SERVO_RIGHT_ANGLE 90
// #define TURNING_SERVO_FRONT_ANGLE 180

// #define TURNING_SERVO_PIN 3

//nrf24l01
#include <SPI.h>
#include "RF24.h"

#define NRF24L01_CE 5
#define NRF24L01_CSN 6

#define NRF24L01_CHANNEL 83             //0-125, 2400MHz + CHANNEL
#define NRF24L01_PA_LEVEL RF24_PA_LOW   //RF24_PA_MIN 
                                        //RF24_PA_LOW
                                        //RF24_PA_HIGH
                                        //RF24_PA_MAX
#define NRF24L01_DATA_RATE RF24_1MBPS   //RF24_250KBPS
                                        //RF24_1MBPS
                                        //RF24_2MBPS
const byte addr[] = "1Node";
const byte pipe = 1;

RF24 radio(NRF24L01_CE, NRF24L01_CSN);

void setup()
{
    //water valve
    // pinMode(WATER_VALVE_TT_MOTOR_IN1, OUTPUT);
    // pinMode(WATER_VALVE_TT_MOTOR_IN2, OUTPUT);

    //turning
    // turning_servo.attach(TURNING_SERVO_PIN);

    //nrf24l01
    Serial.begin(9600);
    radio.begin();
    radio.setChannel(NRF24L01_CE);
    radio.setPALevel(NRF24L01_PA_LEVEL);
    radio.setDataRate(NRF24L01_DATA_RATE);
    radio.openReadingPipe(pipe, addr);
    radio.startListening();

    Serial.println("nRF24L01 ready");
}

void loop()
{
    if(radio.available(&pipe))
    {
        char msg[32] = "";
        radio.read(&msg, sizeof(msg));
        Serial.println(msg);
    }

//    if(msg == "car foward")
//    {
//        // turning_servo.write(TURNING_SERVO_FRONT_ANGLE);
//        Serial.println("car foward");
//    }
//    else if(msg == "car right")
//    {
//        // turning_servo.write(TURNING_SERVO_RIGHT_ANGLE);
//        Serial.println("car right");
//    }
//    else if(msg == "car left")
//    {
//        // turing_servo.write(TURNING_SERVO_LEFT_ANGLE);
//        Serial.println("car left");
//    }
//    else if(msg == "open valve")
//    {
//        // digitalWrite(WATER_VALVE_TT_MOTOR_IN1, HIGH);
//        // digitalWrite(WATER_VALVE_TT_MOTOR_IN2, LOW);
//        Serial.println("open valve");
//    }
//    else if(msg == "close valve")
//    {
//        // digitalWrite(WATER_VALVE_TT_MOTOR_IN1, LOW);
//        // digitalWrite(WATER_VALVE_TT_MOTOR_IN2, HIGH);
//        Serial.println("close valve");
//    }
//    else if(msg == "valve stop")
//    {
//        // digitalWrite(WATER_VALVE_TT_MOTOR_IN1, LOW);
//        // digitalWrite(WATER_VALVE_TT_MOTOR_IN2, LOW);
//        Serial.println("valve stop");
//    }

    delay(50);
}
