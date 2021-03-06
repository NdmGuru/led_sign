/*
  Variables used throughout the program
  Any configuration should be done here.
  
  Written 09/09/2013 - Nathan Metcalf
 */

/* 
 * Pin definitions for the MAX485
 * Not all these are used, depending
 * on the chip, you may need RTS/CTS
 */
// rx
// rciweve/transmitt
// tx
#define rxPin   2
#define ctsPin  3
#define txPin   4

/*
 * Notification LED Pins
 */
#define ledPin  99

/*
 * LCD Pins
 */
#define lcd_d1 8
#define lcd_d2 9
#define lcd_d3 10
#define lcd_d4 11
#define lcd_rs 12
#define lcd_en 13

/*
 * Buttons
 */
#define btn_1 A3
#define btn_2 A2
#define btn_3 A1
#define btn_4 A0
 

/*
 * System bits/password
 */
#define startBit      0x02
#define stopBit       0x03
#define password      0x80

/*
 *System cmds
 */
#define cmdEnable     0xBB
#define cmdDisable    0xBC
#define cmdReset      0xBA
#define cmdPause      0x91

/*
 * Movement cmd's (NB: Rainbow cannot be used with all)
 */
#define cmdHalt       0x8E
#define cmdJump       0x8F
#define cmdRolltop    0x93
#define cmdScrollltr  0x94
#define cmdRollbtm    0x95

/*
 * Color commands
 */
#define Red      0xC0
#define Green    0xC1
#define Yellow   0xC2
#define Rainbow  0xC7 // Cycles through some funky patterns

/*
 * Program variables
 */
#define debug   true
#define repeatInt 6000 // Sleep timer used to not repeat too fast for the sign (Usually when sending one message, with no pause)
