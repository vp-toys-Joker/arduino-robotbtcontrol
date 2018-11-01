#include <SoftwareSerial.h>
#include "EngineClass.h"


//Режимы движения:
const int FORWARD = 0; //вперед
const int BACKWARD = 1; //назад
const int FORWARD_RIGHT = 2; //повернуть направо вперед
const int FORWARD_LEFT = 3; //повернуть налево вперед
const int BACKWARD_RIGHT = 4; //повернуть направо назад
const int BACKWARD_LEFT = 5; //повернуть налево назад
const int ROTATION_LEFT = 6; //вращение на месте влево
const int ROTATION_RIGHT = 7; //вращение на месте вправо
const int SPEED_UP = 8; //общее увеличение скорости
const int SPEED_DOWN = 9; //общее уменьшение скорости
const int LEFT_SPEED_UP = 10; //увеличение скорости левого борта
const int LEFT_SPEED_DOWN = 11; //уменьшение скорости левого борта
const int RIGHT_SPEED_UP = 12; //увеличение скорости правого борта
const int RIGHT_SPEED_DOWN = 13; //уменьшение скорости правого борта
const int SPEED_CONTROL = 14; //общее изменение скорости
const int STOP = 100; //стоп
const int CONTINUE = 101; //продолжать
const int STOP_ALL = 102; //работа прекращена

const int deltaSpeed = 10;
const int L1_MOTOR_PIN = 3;
const int L2_MOTOR_PIN = 4;
const int R1_MOTOR_PIN = 7;
const int R2_MOTOR_PIN = 8;
const int L_PWM_PIN = 11;
const int R_PWM_PIN = 10;
const int RECV_PIN = 12;
const int BLINK_PIN = 13;


int mode;
int speedLeft, speedRight;
float speedK;

SoftwareSerial btSerial(12, 2);

char btInput;


EngineClass Engine(L1_MOTOR_PIN, L2_MOTOR_PIN, L_PWM_PIN, R1_MOTOR_PIN, R2_MOTOR_PIN, R_PWM_PIN);

void setup() {
  // put your setup code here, to run once:
  speedLeft = speedRight = 0;
  speedK = 0.;
  mode = STOP;
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Setup BT");
  btSerial.begin(9600);
}//setup

void loop() {
  // put your main code here, to run repeatedly:
  if (btSerial.available()) {
    btInput = (char)btSerial.read();
    //if (btInput != 'S')
    Serial.println(btInput);
    BTCheckMode(btInput);
  }
  MotorControl(mode);
}//loop

int BTCheckMode(uint8_t key)
{
  switch (key)
  {
    case 'F': //стрелка вверх
      mode = FORWARD;
      break;
    case 'L': //стрелка влево
      mode = ROTATION_LEFT;
      break;
    case 'R': //стрелка вправо
      mode = ROTATION_RIGHT;
      break;
    case 'S': //Отпускание клавишей управления
      mode = STOP;
      break;
    case 'B': //стрелка вниз
      mode = BACKWARD;
      break;
    case 'G'://стрелки вверх и влево
      mode = FORWARD_LEFT;
      break;
    case 'I'://стрелки вверх и вправо
      mode = FORWARD_RIGHT;
      break;
    case 'H'://стрелки вниз и влево
      mode = BACKWARD_LEFT;
      break;
    case 'J'://стрелки вниз и вправо
      mode = BACKWARD_RIGHT;
      break;
    case 'D': //завершение работы управляющей программы на удаленном устройстве
      mode = STOP_ALL;
      break;
      case '0': //скороcть 0%
        mode = SPEED_CONTROL;
        speedK = 0;
        break;
      case '1': //скороcть 10%
        mode = SPEED_CONTROL;
        speedK = 0.1;
        break;
      case '2': //скороcть 20%
        mode = SPEED_CONTROL;
        speedK = 0.2;
        break;
      case '3': //скороcть 30%
        mode = SPEED_CONTROL;
        speedK = 0.3;
        break;
      case '4': //скороcть 40%
        mode = SPEED_CONTROL;
        speedK = 0.4;
        break;
      case '5': //скороcть 50%
        mode = SPEED_CONTROL;
        speedK = 0.5;
        break;
      case '6': //скороcть 60%
        mode = SPEED_CONTROL;
        speedK = 0.6;
        break;
      case '7': //скороcть 70%
        mode = SPEED_CONTROL;
        speedK = 0.7;
        break;
      case '8': //скороcть 80%
        mode = SPEED_CONTROL;
        speedK = 0.8;
        break;
      case '9': //скороcть 90%
        mode = SPEED_CONTROL;
        speedK = 0.9;
        break;
      case 'q': //скороcть 100%
        mode = SPEED_CONTROL;
        speedK = 1;
        break;
      case 'V': //включить звук или что-то другое
//        mode = PARAM_0_ON;
        break;
      case 'v': //выключить звук или что-то другое
//        mode = PARAM_0_OFF;
        break;
      case 'W': //включить фары или что-то другое
//        mode = PARAM_1_ON;
        break;
      case 'w': //выключить фары или что-то другое
//        mode = PARAM_1_OFF;
        break;
      case 'U': //включить задний свет или что-то другое
//        mode = PARAM_2_ON;
        break;
      case 'u': //выключить задний свет или что-то другое
//        mode = PARAM_2_OFF;
        break;
      case 'X': //включить дополнительную опцию или что-то другое
//        mode = PARAM_3_ON;
        break;
      case 'x': //выключить дополнительную опцию или что-то другое
//        mode = PARAM_3_OFF;
        break;
  }
}//BTCheckMode

void MotorControl(int mode)
{
  switch (mode)
  {
    case FORWARD:
      Engine.forward();
      mode = CONTINUE;
      break;
    case BACKWARD:
      Engine.backward();
      mode = CONTINUE;
      break;
    case FORWARD_LEFT:
      Engine.forward_right();
      mode = CONTINUE;
      break;
    case FORWARD_RIGHT:
      Engine.forward_left();
      mode = CONTINUE;
      break;
    case BACKWARD_LEFT:
      Engine.backward_right();
      mode = CONTINUE;
      break;
    case BACKWARD_RIGHT:
      Engine.backward_left();
      mode = CONTINUE;
      break;
    case ROTATION_LEFT:
      Engine.rotation_backward_left_forward_right();
      mode = CONTINUE;
      break;
    case ROTATION_RIGHT:
//      Engine.setspeed(64, 64);
      Engine.rotation_backward_right_forward_left();
      mode = CONTINUE;
      break;
    case SPEED_CONTROL: //общее увеличение скорости
      speedLeft = 255*speedK;
      speedRight = 255*speedK;
      Engine.setspeed(speedLeft, speedRight);
      mode = CONTINUE;
      break;
    case STOP: //остановка движения
      Engine.stopmotors();
      mode = CONTINUE;
      break;
    case STOP_ALL: //завершение движения - приехали
      speedLeft = speedK = 0;
      speedRight = 0;
      Engine.stopmotors();
      Engine.setspeed(speedLeft, speedRight);
      mode = CONTINUE;
      break;
    default: //CONTINUE
      break;
  }
}//void MotorControl

