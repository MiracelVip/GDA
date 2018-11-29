

// ============================================================
// Example:     LCDML_serialmonitor
// ============================================================
// Description:
// This example includes the complete functionality over some
// tabs. All Tabs which are started with "LCDML_display_.."
// generates an output on the display / console / ....
// This example is for the author to test the complete functionality
// ============================================================

// *********************************************************************
// includes
// *********************************************************************
  #include <LiquidCrystal.h>
  #include <LCDMenuLib2.h>
  #include <EEPROM.h>
  #include "OneButton.h"

// *********************************************************************
// LCDML display settings
// *********************************************************************
  // settings for LCD
  #define _LCDML_DISP_cols  16
  #define _LCDML_DISP_rows  2

  #define _LCDML_DISP_cfg_cursor                     0x7E   // cursor Symbol
  #define _LCDML_DISP_cfg_scrollbar                  1      // enable a scrollbar

  // LCD object
  // liquid crystal needs (rs, e, dat4, dat5, dat6, dat7)
  LiquidCrystal lcd(32, 34, 22, 24, 26, 28);

  const uint8_t scroll_bar[5][8] = {
    {B10001, B10001, B10001, B10001, B10001, B10001, B10001, B10001}, // scrollbar top
    {B11111, B11111, B10001, B10001, B10001, B10001, B10001, B10001}, // scroll state 1
    {B10001, B10001, B11111, B11111, B10001, B10001, B10001, B10001}, // scroll state 2
    {B10001, B10001, B10001, B10001, B11111, B11111, B10001, B10001}, // scroll state 3
    {B10001, B10001, B10001, B10001, B10001, B10001, B11111, B11111}  // scrollbar bottom
  };

// *********************************************************************
// Prototypes
// *********************************************************************
  void lcdml_menu_display();
  void lcdml_menu_clear();
  void lcdml_menu_control();

// *********************************************************************
// Global variables
// *********************************************************************
    int g_para_0 = 0;    // Flasche mit CO2 fluten
    int g_para_2 = 0;    // Druck aufbauen
    int g_para_4 = 0;    // Bier einfüllen start
    int g_para_6 = 0;    // Bier einfüllen langsam
    int g_para_8 = 0;    // Bier einfüllen schnell
    int g_para_10 = 0;  // Bier voll
    int g_para_12 = 0;  // Druck ablassen langsam
    int g_para_14 = 0;  // Druck ablassen schnell

    const byte sensor_bottle = 19;
    volatile bool full = false;
    volatile int offset = 0;


    OneButton button_start(20, true);
    OneButton button_stop(21, true);
    OneButton button_clean(39, true);
    OneButton button_manFill(37, true);
    OneButton button_manPressure(35, true);

    const int led_r = 51;
    const int led_g = 53;
    
    const int ventil_bier = 44;
    const int ventil_co2 = 46;
    const int ventil_co2_ab_l = 40;
    const int ventil_co2_ab_s = 42;
// *********************************************************************
// Objects
// *********************************************************************
  LCDMenuLib2_menu LCDML_0 (255, 0, 0, NULL, NULL); // root menu element (do not change)
  LCDMenuLib2 LCDML(LCDML_0, _LCDML_DISP_rows, _LCDML_DISP_cols, lcdml_menu_display, lcdml_menu_clear, lcdml_menu_control);

// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************
  // LCDML_0        => layer 0
  // LCDML_0_X      => layer 1
  // LCDML_0_X_X    => layer 2
  // LCDML_0_X_X_X  => layer 3
  // LCDML_0_...      => layer ...

  // For beginners
  // LCDML_add(id, prev_layer, new_num, lang_char_array, callback_function)
  LCDML_add         (0  , LCDML_0         , 1  , "Automatik Start"      , automatic_filling);
  LCDML_add         (1  , LCDML_0         , 2  , "Einstellungen"    , NULL);     
  
  LCDML_add         (2  , LCDML_0_2       , 1  , "1.0 F\365llen"    , NULL);
  LCDML_add         (3  , LCDML_0_2       , 2  , "2.0 Abblasen"     , NULL);
  LCDML_add         (4  , LCDML_0_2       , 3  , "... speichern"    , save_settings);
  LCDML_add         (5  , LCDML_0_2       , 4  , "Back"             , mFunc_back);

  LCDML_add         (6  , LCDML_0_2_1     , 1  , "1 Co2 fluten"     , NULL);                    // NULL = no menu function
  LCDML_addAdvanced (7  , LCDML_0_2_1     , 2  , NULL,          ""                  , dyn_para_0,                0,   _LCDML_TYPE_dynParam);
  LCDML_add         (8  , LCDML_0_2_1     , 3  , "2 Druck aufbau"   , NULL);                       // NULL = no menu function
  LCDML_addAdvanced (9  , LCDML_0_2_1     , 4  , NULL,          ""                  , dyn_para_2,                0,   _LCDML_TYPE_dynParam);
  LCDML_add         (10  , LCDML_0_2_1     , 5  , "3 Bier start"     , NULL);                       // NULL = no menu function
  LCDML_addAdvanced (11 , LCDML_0_2_1     , 6  , NULL,          ""                  , dyn_para_4,                0,   _LCDML_TYPE_dynParam);
  LCDML_add         (12 , LCDML_0_2_1     , 7  , "4 Bier in +"      , NULL);                       // NULL = no menu function
  LCDML_addAdvanced (13 , LCDML_0_2_1     , 8  , NULL,          ""                  , dyn_para_6,                0,   _LCDML_TYPE_dynParam);
  LCDML_add         (14 , LCDML_0_2_1     , 9  , "5 Bier in ++"     , NULL);                       // NULL = no menu function
  LCDML_addAdvanced (15 , LCDML_0_2_1     , 10 , NULL,          ""                  , dyn_para_8,                0,   _LCDML_TYPE_dynParam);
  LCDML_add         (16 , LCDML_0_2_1     , 11 , "6 Bier voll"      , NULL);                       // NULL = no menu function
  LCDML_addAdvanced (17 , LCDML_0_2_1     , 12 , NULL,          ""                  , dyn_para_10,                0,   _LCDML_TYPE_dynParam);
  LCDML_add         (18 , LCDML_0_2_1     , 13  , "7 Druck ab -"     , NULL);                       // NULL = no menu function
  LCDML_addAdvanced (19 , LCDML_0_2_1     , 14 , NULL,          ""                  , dyn_para_12,                0,   _LCDML_TYPE_dynParam);
  LCDML_add         (20 , LCDML_0_2_1     , 15  , "8 Druck ab --"    , NULL);                       // NULL = no menu function
  LCDML_addAdvanced (21 , LCDML_0_2_1     , 16 , NULL,          ""                  , dyn_para_14,                0,   _LCDML_TYPE_dynParam);
  LCDML_add         (22 , LCDML_0_2_1     , 17  , "Back"             , mFunc_back);              // this menu function can be found on "LCDML_display_menuFunction" tab
  LCDML_add         (23 , LCDML_0         , 3   , "M_Fill"           , manual_fill);    
  LCDML_add         (24 , LCDML_0         , 4   , "M_Pressure"       , manual_pressure);
  LCDML_add         (25 , LCDML_0         , 5   , "clean"       , clean);            


  // menu element count - last element id
  // this value must be the same as the last menu element
  #define _LCDML_DISP_cnt    25

  // create menu
  LCDML_createMenu(_LCDML_DISP_cnt);

// *********************************************************************
// SETUP
// *********************************************************************
  void setup()
  {
    // Set variables
    g_para_0 = eepromReadInt(0);    // Flasche mit CO2 fluten
    if (g_para_0 == -1){g_para_0 += 1;}
    g_para_2 = eepromReadInt(2);    // Druck aufbauen
    if (g_para_2 == -1){g_para_2 += 1;}
    g_para_4 = eepromReadInt(4);    // Bier einfüllen start
    if (g_para_4 == -1){g_para_4 += 1;}
    g_para_6 = eepromReadInt(6);    // Bier einfüllen langsam
    if (g_para_6 == -1){g_para_6 += 1;}
    g_para_8 = eepromReadInt(8);    // Bier einfüllen schnell
    if (g_para_8 == -1){g_para_8 += 1;}
    g_para_10 = eepromReadInt(10);  // Bier voll
    if (g_para_10 == -1){g_para_10 += 1;}
    g_para_12 = eepromReadInt(12);  // Druck ablassen langsam
    if (g_para_12 == -1){g_para_12 += 1;}
    g_para_14 = eepromReadInt(14);  // Druck ablassen schnell
    if (g_para_14 == -1){g_para_14 += 1;}

    // Set ventils
    pinMode(ventil_bier, OUTPUT);
    pinMode(ventil_co2, OUTPUT);
    pinMode(ventil_co2_ab_l, OUTPUT);
    pinMode(ventil_co2_ab_s, OUTPUT);

    digitalWrite(ventil_bier, LOW);
    digitalWrite(ventil_co2, LOW);
    digitalWrite(ventil_co2_ab_l, LOW);
    digitalWrite(ventil_co2_ab_s, LOW);

    pinMode(led_r, OUTPUT);
    pinMode(led_g, OUTPUT);

    // Set Buttons
    pinMode(20, INPUT_PULLUP);
    button_start.attachClick(b_start);
    pinMode(21, INPUT_PULLUP);
    button_stop.attachClick(b_stop);
    pinMode(35, INPUT_PULLUP);
    button_manPressure.attachClick(b_manualPressure);
    pinMode(37, INPUT_PULLUP);
    button_manFill.attachClick(b_manualFill);
    pinMode(39, INPUT_PULLUP);
    button_clean.attachClick(b_clean);

    
    // Set Sensor
    pinMode(sensor_bottle, INPUT_PULLUP);
     
    
    
    // serial init; only be needed if serial control is used
    Serial.begin(9600);                // start serial
    Serial.println(F(_LCDML_VERSION)); // only for examples

    // LCD Begin
    lcd.begin(_LCDML_DISP_cols,_LCDML_DISP_rows);
    // set special chars for scrollbar
    lcd.createChar(0, (uint8_t*)scroll_bar[0]);
    lcd.createChar(1, (uint8_t*)scroll_bar[1]);
    lcd.createChar(2, (uint8_t*)scroll_bar[2]);
    lcd.createChar(3, (uint8_t*)scroll_bar[3]);
    lcd.createChar(4, (uint8_t*)scroll_bar[4]);

    // LCDMenuLib Setup
    LCDML_setup(_LCDML_DISP_cnt);

    // Some settings which can be used

    // Enable Menu Rollover
    LCDML.MENU_enRollover();

    // Enable Screensaver (screensaver menu function, time to activate in ms)
    LCDML.SCREEN_enable(mFunc_screensaver, 10000); // set to 10 seconds
    //LCDML.SCREEN_disable();

    // Some needful methods

    // You can jump to a menu function from anywhere with
    //LCDML.OTHER_jumpToFunc(mFunc_p2); // the parameter is the function name
    
  }

// *********************************************************************
// LOOP
// *********************************************************************
  void loop()
  {
    LCDML.loop();
    button_start.tick();
    button_stop.tick();
    button_manPressure.tick();
    button_manFill.tick();
    button_clean.tick();
  }

// *********************************************************************
// check some errors - do not change here anything
// *********************************************************************
# if(_LCDML_DISP_rows > _LCDML_DISP_cfg_max_rows)
# error change value of _LCDML_DISP_cfg_max_rows in LCDMenuLib2.h
# endif
