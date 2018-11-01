#ifndef __EngineClass_h_v0_001_180904__
#define __EngineClass_h_v0_001_180904__

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif 

#define _OPTIMIZATION_SPEED_ 0

class EngineClass
{
#if (_OPTIMIZATION_SPEED_ == 1)
  volatile uint8_t *motor_L1, *motor_L2;
  volatile uint8_t *motor_R1, *motor_R2;
  uint8_t analog_L, bit_L1, bit_L2, analog_R, bit_R1, bit_R2;
  void turnOffPWM(uint8_t timer);
#else
  uint8_t motor_L1, motor_L2, analog_L;
  uint8_t motor_R1, motor_R2, analog_R;
#endif
  public:
    EngineClass(uint8_t L1, uint8_t L2, uint8_t iL, uint8_t R1, uint8_t R2, uint8_t iR);
    ~EngineClass(){};

    void setspeed(int LeftSpeed, int RightSpeed);
    void forward(); //вперед оба борта
    void forward_left(); //левый борт вперед, правый стоп
    void forward_right(); //правый борт вперед, левый стоп
    void backward(); //назад оба борта
    void backward_left();//левый борт назад, правый стоп
    void backward_right();//правый борт назад, левый стоп
    void rotation_backward_left_forward_right(); //вращение: левый борт назад, правый вперед
    void rotation_backward_right_forward_left(); //вращение: правый назад, левый борт вперед
    void stopmotors();
#if (_OPTIMIZATION_SPEED_ == 1)
  bool initError;
#endif    
};

#endif //__EngineClass_h_v0_001_180904__
