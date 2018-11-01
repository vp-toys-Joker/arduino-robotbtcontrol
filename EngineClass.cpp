
#include "EngineClass.h"



EngineClass::EngineClass(uint8_t L1, uint8_t L2, uint8_t iL, uint8_t R1, uint8_t R2, uint8_t iR)
{
#if (_OPTIMIZATION_SPEED_ == 1)
  initError = true;
  motor_L1 = motor_L2 = motor_R1 = motor_R2 = 0;
  uint8_t port = digitalPinToPort(L1);
  if (port == NOT_A_PIN) return;
  motor_L1 = portOutputRegister(port);
  port = digitalPinToPort(L2);
  if (port == NOT_A_PIN) return;
  motor_L2 = portOutputRegister(port);
  port = digitalPinToPort(R1);
  if (port == NOT_A_PIN) return;
  motor_R1 = portOutputRegister(port);
  port = digitalPinToPort(R2);
  if (port == NOT_A_PIN) return;
  motor_R2 = portOutputRegister(port);

  uint8_t timer = digitalPinToTimer(L1);
  if (timer != NOT_ON_TIMER) turnOffPWM(timer);
  timer = digitalPinToTimer(L2);
  if (timer != NOT_ON_TIMER) turnOffPWM(timer);
  timer = digitalPinToTimer(R1);
  if (timer != NOT_ON_TIMER) turnOffPWM(timer);
  timer = digitalPinToTimer(R2);
  if (timer != NOT_ON_TIMER) turnOffPWM(timer);
  bit_L1 = digitalPinToBitMask(L1);
  bit_L2 = digitalPinToBitMask(L2);
  bit_R1 = digitalPinToBitMask(R1);
  bit_R2 = digitalPinToBitMask(R2);
  analog_L = iL;
  analog_R = iR;
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(analog_L, OUTPUT);
  pinMode(analog_R , OUTPUT);
  setspeed(0, 0);
  initError = false;
#else
  motor_L1 = L1;
  motor_L2 = L2;
  analog_L = iL;
  motor_R1 = R1;
  motor_R2 = R2;
  analog_R = iR;

  pinMode(motor_L1, OUTPUT);
  pinMode(motor_L2, OUTPUT);
  pinMode(motor_R1, OUTPUT);
  pinMode(motor_R2, OUTPUT);
  pinMode(analog_L, OUTPUT);
  pinMode(analog_R, OUTPUT);
  setspeed(0, 0);
#endif
}//EngineClass::EngineClass

void EngineClass::setspeed(int LeftSpeed, int RightSpeed)
{
  analogWrite(analog_L, LeftSpeed);
  analogWrite(analog_R, RightSpeed);
}//EngineClass::setspeed

void EngineClass::forward()
{
#if (_OPTIMIZATION_SPEED_ == 1)
  uint8_t oldSREG = SREG;
  cli();

  // LOW
  *motor_L2 &= ~bit_L2;
  *motor_R2 &= ~bit_R2;
  // HIGH
  *motor_L1 |= bit_L1;
  *motor_R1 |= bit_R1;

  SREG = oldSREG;
#else
  digitalWrite(motor_L1, HIGH);
  digitalWrite(motor_L2, LOW);
  digitalWrite(motor_R1, HIGH);
  digitalWrite(motor_R2, LOW);
#endif
}//EngineClass::forward

void EngineClass::forward_left()
{
#if (_OPTIMIZATION_SPEED_ == 1)
  uint8_t oldSREG = SREG;
  cli();

  // LOW
  *motor_L1 &= ~bit_L1;
  *motor_L2 &= ~bit_L2;
  *motor_R2 &= ~bit_R2;
  // HIGH
  *motor_R1 |= bit_R1;

  SREG = oldSREG;
#else
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_L2, LOW);
  digitalWrite(motor_R1, HIGH);
  digitalWrite(motor_R2, LOW);
#endif
}//EngineClass::forward_left

void EngineClass::forward_right()
{
#if (_OPTIMIZATION_SPEED_ == 1)
  uint8_t oldSREG = SREG;
  cli();

  // LOW
  *motor_L2 &= ~bit_L2;
  *motor_R1 &= ~bit_R1;
  *motor_R2 &= ~bit_R2;
  // HIGH
  *motor_L1 |= bit_L1;

  SREG = oldSREG;
#else
  digitalWrite(motor_L1, HIGH);
  digitalWrite(motor_L2, LOW);
  digitalWrite(motor_R1, LOW);
  digitalWrite(motor_R2, LOW);
#endif
}//EngineClass::forward_right

void EngineClass::backward()
{
#if (_OPTIMIZATION_SPEED_ == 1)
  uint8_t oldSREG = SREG;
  cli();

  // LOW
  *motor_L1 &= ~bit_L1;
  *motor_R1 &= ~bit_R1;
  // HIGH
  *motor_R2 |= bit_R2;
  *motor_L1 |= bit_L1;

  SREG = oldSREG;
#else
  digitalWrite(motor_L2, HIGH);
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_R2, HIGH);
  digitalWrite(motor_R1, LOW);
#endif
}//EngineClass::backward

void EngineClass::backward_left()
{
#if (_OPTIMIZATION_SPEED_ == 1)
  uint8_t oldSREG = SREG;
  cli();

  // LOW
  *motor_L1 &= ~bit_L1;
  *motor_L2 &= ~bit_L2;
  *motor_R1 &= ~bit_R1;
  // HIGH
  *motor_R2 |= bit_R2;

  SREG = oldSREG;
#else
  digitalWrite(motor_L2, LOW);
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_R2, HIGH);
  digitalWrite(motor_R1, LOW);
#endif
}//EngineClass::backward_left

void EngineClass::backward_right()
{
#if (_OPTIMIZATION_SPEED_ == 1)
  uint8_t oldSREG = SREG;
  cli();

  // LOW
  *motor_L1 &= ~bit_L1;
  *motor_R1 &= ~bit_R1;
  *motor_R2 &= ~bit_R2;
  // HIGH
  *motor_L2 |= bit_L2;

  SREG = oldSREG;
#else
  digitalWrite(motor_L2, HIGH);
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_R2, LOW);
  digitalWrite(motor_R1, LOW);
#endif
}//EngineClass::backward_right

void EngineClass::rotation_backward_left_forward_right()
{
#if (_OPTIMIZATION_SPEED_ == 1)
  uint8_t oldSREG = SREG;
  cli();

  // LOW
  *motor_L2 &= ~bit_L2;
  *motor_R1 &= ~bit_R1;
  // HIGH
  *motor_L1 |= bit_L1;
  *motor_R2 |= bit_R2;

  SREG = oldSREG;
#else
  digitalWrite(motor_L1, HIGH);
  digitalWrite(motor_L2, LOW);
  digitalWrite(motor_R1, LOW);
  digitalWrite(motor_R2, HIGH);
#endif
}//EngineClass::rotation_left

void EngineClass::rotation_backward_right_forward_left()
{
#if (_OPTIMIZATION_SPEED_ == 1)
  uint8_t oldSREG = SREG;
  cli();

  // LOW
  *motor_L1 &= ~bit_L1;
  *motor_R2 &= ~bit_R2;
  // HIGH
  *motor_L2 |= bit_L2;
  *motor_R1 |= bit_R1;

  SREG = oldSREG;
#else
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_L2, HIGH);
  digitalWrite(motor_R1, HIGH);
  digitalWrite(motor_R2, LOW);
#endif
}//EngineClass::rotation_right

void EngineClass::stopmotors()
{
#if (_OPTIMIZATION_SPEED_ == 1)
  uint8_t oldSREG = SREG;
  cli();

  // All LOW
  *motor_L1 &= ~bit_L1;
  *motor_L2 &= ~bit_L2;
  *motor_R2 &= ~bit_R2;
  *motor_R1 &= ~bit_R1;

  SREG = oldSREG;
#else
  digitalWrite(motor_L1, LOW);
  digitalWrite(motor_L2, LOW);
  digitalWrite(motor_R1, LOW);
  digitalWrite(motor_R2, LOW);
#endif
}//EngineClass::stopmotors

//#ifdef _OPTIMIZATION_SPEED_
//#endif
#if (_OPTIMIZATION_SPEED_ == 1)

#include <wiring_private.h>

void EngineClass::turnOffPWM(uint8_t timer)
{
  switch (timer)
  {
    #if defined(TCCR1A) && defined(COM1A1)
    case TIMER1A:   cbi(TCCR1A, COM1A1);    break;
    #endif
    #if defined(TCCR1A) && defined(COM1B1)
    case TIMER1B:   cbi(TCCR1A, COM1B1);    break;
    #endif
    #if defined(TCCR1A) && defined(COM1C1)
    case TIMER1C:   cbi(TCCR1A, COM1C1);    break;
    #endif
    
    #if defined(TCCR2) && defined(COM21)
    case  TIMER2:   cbi(TCCR2, COM21);      break;
    #endif
    
    #if defined(TCCR0A) && defined(COM0A1)
    case  TIMER0A:  cbi(TCCR0A, COM0A1);    break;
    #endif
    
    #if defined(TCCR0A) && defined(COM0B1)
    case  TIMER0B:  cbi(TCCR0A, COM0B1);    break;
    #endif
    #if defined(TCCR2A) && defined(COM2A1)
    case  TIMER2A:  cbi(TCCR2A, COM2A1);    break;
    #endif
    #if defined(TCCR2A) && defined(COM2B1)
    case  TIMER2B:  cbi(TCCR2A, COM2B1);    break;
    #endif
    
    #if defined(TCCR3A) && defined(COM3A1)
    case  TIMER3A:  cbi(TCCR3A, COM3A1);    break;
    #endif
    #if defined(TCCR3A) && defined(COM3B1)
    case  TIMER3B:  cbi(TCCR3A, COM3B1);    break;
    #endif
    #if defined(TCCR3A) && defined(COM3C1)
    case  TIMER3C:  cbi(TCCR3A, COM3C1);    break;
    #endif

    #if defined(TCCR4A) && defined(COM4A1)
    case  TIMER4A:  cbi(TCCR4A, COM4A1);    break;
    #endif          
    #if defined(TCCR4A) && defined(COM4B1)
    case  TIMER4B:  cbi(TCCR4A, COM4B1);    break;
    #endif
    #if defined(TCCR4A) && defined(COM4C1)
    case  TIMER4C:  cbi(TCCR4A, COM4C1);    break;
    #endif      
    #if defined(TCCR4C) && defined(COM4D1)
    case TIMER4D: cbi(TCCR4C, COM4D1);  break;
    #endif      
      
    #if defined(TCCR5A)
    case  TIMER5A:  cbi(TCCR5A, COM5A1);    break;
    case  TIMER5B:  cbi(TCCR5A, COM5B1);    break;
    case  TIMER5C:  cbi(TCCR5A, COM5C1);    break;
    #endif
  }
}//void EngineClass::turnOffPWM(uint8_t timer)
#endif



