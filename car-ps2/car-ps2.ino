//water valve
#define WATER_VALVE_IN1 2
#define WATER_VALVE_IN2 4

//turning
#include <Servo.h>
Servo turning_servo;

#define TURNING_SERVO_LEFT_ANGLE 0
#define TURNING_SERVO_RIGHT_ANGLE 90
#define TURNING_SERVO_FRONT_ANGLE 180

#define TURNING_SERVO_PIN 3

//brake
bool brake_state = false;                   //true for activated

Servo brake_servo_left;
#define BRAKE_SERVO_LEFT_ON_ANGLE 0
#define BRAKE_SERVO_LEFT_OFF_ANGLE 180
#define BRAKE_SERVO_LEFT_PIN 9

Servo brake_servo_right;
#define BRAKE_SERVO_RIGHT_ON_ANGLE 0
#define BRAKE_SERVO_RIGHT_OFF_ANGLE 180
#define BRAKE_SERVO_RIGHT_PIN 10

//nrf24l01
// #include <SPI.h>
// #include "RF24.h"

// #define NRF24L01_CE 5
// #define NRF24L01_CSN 6

// #define NRF24L01_CHANNEL 83             //0-125, 2400MHz + CHANNEL
// #define NRF24L01_PA_LEVEL RF24_PA_LOW   //RF24_PA_MIN 
//                                         //RF24_PA_LOW
//                                         //RF24_PA_HIGH
//                                         //RF24_PA_MAX
// #define NRF24L01_DATA_RATE RF24_1MBPS   //RF24_250KBPS
//                                         //RF24_1MBPS
//                                         //RF24_2MBPS
// const byte addr[] = "1Node";
// const byte pipe = 1;

// RF24 radio(NRF24L01_CE, NRF24L01_CSN);

//ps2

#define DATA_PORT 5
#define COMMAND_PORT 6
#define ATT_PORT 7
#define CLK_PORT 8
#define SUPPORT_ANALOG_JOYSTICK true
#define SUPPORT_VIBRATION true

PS2X ps2x;
int error = 0;
byte type = 0;
byte vibrate = 0;

void setup()
{
    Serial.begin(9600);
    Serial.println("");
    Serial.println("start");

    //water valve
    pinMode(WATER_VALVE_IN1, OUTPUT);
    pinMode(WATER_VALVE_IN2, OUTPUT);

    //turning
    turning_servo.attach(TURNING_SERVO_PIN);

    //brake
    brake_servo_left.attach(BRAKE_SERVO_LEFT_PIN);
    brake_servo_right.attach(BRAKE_SERVO_RIGHT_PIN);

    //nrf24l01
    // Serial.begin(9600);
    // radio.begin();
    // radio.setChannel(NRF24L01_CE);
    // radio.setPALevel(NRF24L01_PA_LEVEL);
    // radio.setDataRate(NRF24L01_DATA_RATE);
    // radio.openReadingPipe(pipe, addr);
    // radio.startListening();

    // Serial.println("nRF24L01 ready");

    //ps2x
    do
    {
        error = ps2x.config_gamepad(CLK_PORT, COMMAND_PORT, ATT_PORT, DATA_PORT, SUPPORT_ANALOG_JOYSTICK, SUPPORT_VIBRATION);
        if(error == 0)
            Serial.println("Controller found");
        else if(error == 1)
            Serial.println("ERROR: No Controller found");
        else if(error == 2)
            Serial.println("ERROR: Controller not accepting command");
        else if(error == 3)
            Serial.println("ERROR: Controller refusing to enter Pressures Mode, may not support it");
    }while(error != 0);
}

void loop()
{
    // if(radio.available(&pipe))
    // {
    //     char msg[32] = "";
    //     radio.read(&msg, sizeof(msg));
    //     Serial.println(msg);
    // }
    if(error == 1)      return;

    ps2x.read_gamepad(false, vibrate);

    char msg[32] = "";
    if(ps2x.Button(PSB_PAD_UP))
        msg = "car foward";
    else if(ps2x.Button(PSB_PAD_RIGHT))
        msg = "car right";
    else if(ps2x.Button(PSB_PAD_LEFT))
        msg = "car left";
    else if(ps2x.Button(PSB_BLUE))
        msg = "open valve";
    else if(ps2x.Button(PSB_RED))
        msg = "close valve";
    else if(ps2x.Button(PSB_GREEN))
        msg = "car brake";

    if(msg == "car foward")
    {
        turning_servo.write(TURNING_SERVO_FRONT_ANGLE);
        brake_servo_left.write(BRAKE_SERVO_LEFT_OFF_ANGLE);
        brake_servo_right.write(BRAKE_SERVO_RIGHT_OFF_ANGLE);
        brake_state = false;
    }
    else if(msg == "car right")
    {
        turning_servo.write(TURNING_SERVO_RIGHT_ANGLE);
        brake_servo_left.write(BRAKE_SERVO_LEFT_OFF_ANGLE);
        brake_servo_right.write(BRAKE_SERVO_RIGHT_OFF_ANGLE);
        brake_state = false;
    }
    else if(msg == "car left")
    {
        turing_servo.write(TURNING_SERVO_LEFT_ANGLE);
        brake_servo_left.write(BRAKE_SERVO_LEFT_OFF_ANGLE);
        brake_servo_right.write(BRAKE_SERVO_RIGHT_OFF_ANGLE);
        brake_state = false;
    }
    else if(msg == "open valve")
    {
        digitalWrite(WATER_VALVE_IN1, HIGH);
        digitalWrite(WATER_VALVE_IN2, LOW);
    }
    else if(msg == "close valve")
    {
        digitalWrite(WATER_VALVE_IN1, LOW);
        digitalWrite(WATER_VALVE_IN2, LOW);
    }
    else if(msg == "valve stop")
    {
        // digitalWrite(WATER_VALVE_IN1, LOW);
        // digitalWrite(WATER_VALVE_IN2, LOW);
    }
    else if(msg == "car brake")
    {
        if(brake_state == false)
        {
            brake_servo_left.write(BRAKE_SERVO_LEFT_ON_ANGLE);
            brake_servo_right.write(BRAKE_SERVO_RIGHT_ON_ANGLE);
            brake_state = true;
        }
        else if(brake_state == true)
        {
            brake_servo_left.write(BRAKE_SERVO_LEFT_OFF_ANGLE);
            brake_servo_right.write(BRAKE_SERVO_RIGHT_OFF_ANGLE);
            brake_state = false;
        }
    }

    delay(50);
}