#ifndef _HELPERMACROS_H_
#define _HELPERMACROS_H_

#define SPRINT(txt) { Serial.print("\n"); Serial.print(millis()); Serial.print("\t\t"); Serial.print(#txt); };

#define PRINT_ARRAY_DATA 0
#define PRINT_MOTOR_SPEED 0
#define PRINT_WALL_HIT_DATA 1
#define PRINT_STATE_CHANGES 0
#define PRINT_USER_INPUT 0

#endif
