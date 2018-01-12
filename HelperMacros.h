#ifndef _HELPERMACROS_H_
#define _HELPERMACROS_H_

#define SPRINT(txt) { Serial.print("\n"); Serial.print(millis()); Serial.print("\t\t"); Serial.print(#txt); Serial.print('\0'); };

#define PRINT_ARRAY_DATA 0
#define PRINT_MOTOR_SPEED 0
#define PRINT_WALL_HIT_DATA 1
#define PRINT_STATE_CHANGES 1
#define PRINT_USER_INPUT 0
#define PRINT_SONAR_PING 1

#define CRB_REG_M_2_5GAUSS 0x60 // CRB_REG_M value for magnetometer +/-2.5 gauss full scale
#define CRA_REG_M_220HZ    0x1C // CRA_REG_M value for magnetometer 220 Hz update rate

#endif
