/* ===================================================================== *
 *                                                                       *
 * Menu Callback Function                                                *
 *                                                                       *
 * ===================================================================== *
 *
 * EXAMPLE CODE:

// *********************************************************************
void your_function_name(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // setup
    // is called only if it is started

    // starts a trigger event for the loop function every 100 milliseconds
    LCDML.FUNC_setLoopInterval(100);
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // loop
    // is called when it is triggered
    // - with LCDML_DISP_triggerMenu( milliseconds )
    // - with every button status change

    // check if any button is pressed (enter, up, down, left, right)
    if(LCDML.BT_checkAny()) {
      LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // loop end
    // you can here reset some global vars or delete it
  }
}


 * ===================================================================== *
 */

// *********************************************************************
void eepromWriteInt(int adr, int wert) {
// *********************************************************************
  byte low, high;
  low=wert&0xFF;
  high=(wert>>8)&0xFF;
  EEPROM.write(adr, low); // dauert 3,3ms 
  EEPROM.write(adr+1, high);
  return;
}
// *********************************************************************
int eepromReadInt(int adr) {
// *********************************************************************
  byte low, high;
  low=EEPROM.read(adr);
  high=EEPROM.read(adr+1);
  return low + ((high << 8)&0xFF00);
} 


// *********************************************************************
void save_settings(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup()){          // ****** SETUP *********
      eepromWriteInt(0, g_para_0);
      eepromWriteInt(2, g_para_2);
      eepromWriteInt(4, g_para_4);
      eepromWriteInt(6, g_para_6);
      eepromWriteInt(8, g_para_8);
      eepromWriteInt(10, g_para_10);
      eepromWriteInt(12, g_para_12);
      eepromWriteInt(14, g_para_14);
    lcd.setCursor(0, 0);
    lcd.print(F("* gespeichert *"));
    lcd.setCursor(0, 1);
    lcd.print(F("...Taste dr\365cken"));
  }

  if(LCDML.FUNC_loop()){           // ****** LOOP *********
    if(LCDML.BT_checkAny()) { // check if any button is pressed (enter, up, down, left, right)
      // LCDML_goToMenu stops a running menu function and goes to the menu
      LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}
  unsigned long startMillis = millis();
  unsigned long previousMillis = 0;
  unsigned long step1 = startMillis + g_para_0;
  unsigned long step2 = step1 + g_para_2;
  unsigned long step3 = step2 + g_para_4;
  unsigned long step4 = step3 + g_para_6;
  unsigned long step5 = step4 + g_para_8;
  unsigned long step6 = step5 + g_para_10;
  unsigned long step7 = step6 + g_para_12;
  unsigned long step8 = step7 + g_para_14;
uint8_t g_func_timer_info1 = 0;  // time counter (global variable)
unsigned long g_timer_11 = 0; 
// *********************************************************************
void automatic_filling(uint8_t param){


    
// *********************************************************************
  if(LCDML.FUNC_setup()){          // ****** SETUP *********
  // Time Calculation
  
    startMillis = millis();
    previousMillis = 0;
    
    step1 = startMillis + g_para_0;
    step2 = step1 + g_para_2;
    step3 = step2 + g_para_4;
    step4 = step3 + g_para_6;
    step5 = step4 + g_para_8;
    step6 = step5 + g_para_10;
    step7 = step6 + g_para_12;
    step8 = step7 + g_para_14;
     Serial.print("s1: "); Serial.println(step1);
     Serial.print("s2: "); Serial.println(step2);
     Serial.print("s3: "); Serial.println(step3);
     Serial.print("s4: "); Serial.println(step4);
     Serial.print("s5: "); Serial.println(step5);
     Serial.print("s6: "); Serial.println(step6);
     Serial.print("s7: "); Serial.println(step7);
     Serial.print("s8: "); Serial.println(step8);

    lcd.setCursor(0, 0);
    lcd.print(F("* Automatik *"));
    lcd.setCursor(0, 1);
    lcd.print(F("..."));
    digitalWrite(ventil_co2, LOW);
    digitalWrite(ventil_bier, LOW);
    digitalWrite(ventil_co2_ab_l, LOW);
    digitalWrite(ventil_co2_ab_s, LOW);  

    LCDML.FUNC_setLoopInterval(5);  // starts a trigger event for the loop function every 100 milliseconds
//    LCDML.TIMER_msReset(g_timer_1);

  }

  if(LCDML.FUNC_loop()){           // ****** LOOP *********
    // reset screensaver timer
    LCDML.SCREEN_resetTimer();
    
    unsigned long currentMillis = millis();
    Serial.print("current: ");Serial.print(currentMillis);
    Serial.print("startMillis: ");Serial.print(startMillis);
    Serial.print("step1: ");Serial.print(step1);
    Serial.print("step2: ");Serial.println(step2);

    if (currentMillis > startMillis && currentMillis < step1){
        digitalWrite(led_g, HIGH);
        digitalWrite(led_r, LOW);
        
        lcd.setCursor(0, 0);
        lcd.print(F("* CO2 fluten *  "));
        digitalWrite(ventil_bier, LOW);
        digitalWrite(ventil_co2, HIGH);
        digitalWrite(ventil_co2_ab_l, HIGH);
        digitalWrite(ventil_co2_ab_s, LOW);       
    }
    if (currentMillis > step1 && currentMillis < step2){
        lcd.setCursor(0, 0);
        lcd.print(F("* Druck aufbau *"));
        digitalWrite(ventil_bier, LOW);
        digitalWrite(ventil_co2, HIGH);
        digitalWrite(ventil_co2_ab_l, LOW);
        digitalWrite(ventil_co2_ab_s, LOW);
    }
    if (currentMillis > step2 && currentMillis < step3){
        lcd.setCursor(0, 0);
        lcd.print(F("* Bier Start *  "));
        digitalWrite(ventil_bier, HIGH);
        digitalWrite(ventil_co2, LOW);
        digitalWrite(ventil_co2_ab_l, LOW);
        digitalWrite(ventil_co2_ab_s, LOW);
    }
    if (currentMillis > step3 && currentMillis < step4){
        lcd.setCursor(0, 0);
        lcd.print(F("* Bier in + *   "));
        digitalWrite(ventil_bier, HIGH);
        digitalWrite(ventil_co2, LOW);
        digitalWrite(ventil_co2_ab_l, HIGH);
        digitalWrite(ventil_co2_ab_s, LOW);
    }
     if (currentMillis > step4 && currentMillis < step5){
        lcd.setCursor(0, 0);
        lcd.print(F("* Bier in ++ *  "));
        digitalWrite(ventil_bier, HIGH);
        digitalWrite(ventil_co2, LOW);
        digitalWrite(ventil_co2_ab_l, HIGH);
        digitalWrite(ventil_co2_ab_s, HIGH);
    }
    if (currentMillis > step5 && currentMillis < step6){
        lcd.setCursor(0, 0);
        lcd.print(F("* Bier voll *   "));
        digitalWrite(ventil_bier, LOW);
        digitalWrite(ventil_co2, LOW);
        digitalWrite(ventil_co2_ab_l, LOW);
        digitalWrite(ventil_co2_ab_s, LOW);
    }
    if (currentMillis > step6 && currentMillis < step7){
        lcd.setCursor(0, 0);
        lcd.print(F("* Druck ab - *  "));
        digitalWrite(ventil_bier, LOW);
        digitalWrite(ventil_co2, LOW);
        digitalWrite(ventil_co2_ab_l, HIGH);
        digitalWrite(ventil_co2_ab_s, LOW);
    }
    if (currentMillis > step7 && currentMillis < step8){
        lcd.setCursor(0, 0);
        lcd.print(F("* Druck ab -- * "));
        digitalWrite(ventil_bier, LOW);
        digitalWrite(ventil_co2, LOW);
        digitalWrite(ventil_co2_ab_l, HIGH);
        digitalWrite(ventil_co2_ab_s, HIGH);
    }
    if (currentMillis > step8)
    {
        digitalWrite(led_g, LOW);
        digitalWrite(led_r, HIGH);
      // leave this function
      LCDML.FUNC_goBackToMenu();
    }

    

  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}




// *********************************************************************
void mFunc_information(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // setup function
    lcd.setCursor(0, 0);
    lcd.print(F("To close this"));
    lcd.setCursor(0, 1);
    lcd.print(F("function press"));
    lcd.setCursor(0, 2);
    lcd.print(F("any button or use"));
    lcd.setCursor(0, 3);
    lcd.print(F("back button"));
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function
    if(LCDML.BT_checkAny()) { // check if any button is pressed (enter, up, down, left, right)
      // LCDML_goToMenu stops a running menu function and goes to the menu
      LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}


// *********************************************************************
uint8_t g_func_timer_info = 0;  // time counter (global variable)
unsigned long g_timer_1 = 0;    // timer variable (global variable)
void mFunc_timer_info(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    lcd.print(F("20 sec wait")); // print some content on first row
    g_func_timer_info = 20;       // reset and set timer
    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds

    LCDML.TIMER_msReset(g_timer_1);
  }


  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
    // the quit button works in every DISP function without any checks; it starts the loop_end function

    // reset screensaver timer
    LCDML.SCREEN_resetTimer();

    // this function is called every 100 milliseconds

    // this method checks every 1000 milliseconds if it is called
    if(LCDML.TIMER_ms(g_timer_1, 1000)) {
      g_func_timer_info--;                // increment the value every second
      lcd.setCursor(0, 0);                // set cursor pos
      lcd.print(F("  "));
      lcd.setCursor(0, 0);                // set cursor pos
      lcd.print(g_func_timer_info);       // print the time counter value
    }

    // this function can only be ended when quit button is pressed or the time is over
    // check if the function ends normally
    if (g_func_timer_info <= 0)
    {
      // leave this function
      LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}


// *********************************************************************
uint8_t g_button_value = 0; // button value counter (global variable)
void mFunc_p2(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // setup function
    // print LCD content
    // print LCD content
    lcd.setCursor(0, 0);
    lcd.print(F("press left or up"));
    lcd.setCursor(0, 1);
    lcd.print(F("count: 0 of 3"));
    // Reset Button Value
    g_button_value = 0;

    // Disable the screensaver for this function until it is closed
    LCDML.FUNC_disableScreensaver();

  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // the quit button works in every DISP function without any checks; it starts the loop_end function
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      if (LCDML.BT_checkLeft() || LCDML.BT_checkUp()) // check if button left is pressed
      {
        LCDML.BT_resetLeft(); // reset the left button
        LCDML.BT_resetUp(); // reset the left button
        g_button_value++;

        // update LCD content
        // update LCD content
        lcd.setCursor(7, 1); // set cursor
        lcd.print(g_button_value); // print change content
      }
    }

    // check if button count is three
    if (g_button_value >= 3) {
      LCDML.FUNC_goBackToMenu();      // leave this function
    }
  }

  if(LCDML.FUNC_close())     // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}



// *********************************************************************
void mFunc_screensaver(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // update LCD content
    lcd.setCursor(0, 0); // set cursor
    lcd.print("screensaver"); // print change content
    lcd.setCursor(0, 1); // set cursor
    lcd.print("press any key");
    lcd.setCursor(0, 2); // set cursor
    lcd.print("to leave it");
    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds
  }

  if(LCDML.FUNC_loop())
  {
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      LCDML.FUNC_goBackToMenu();  // leave this function
    }
  }

  if(LCDML.FUNC_close())
  {
    // The screensaver go to the root menu
    LCDML.MENU_goRoot();
  }
}



// *********************************************************************
void mFunc_back(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // end function and go an layer back
    LCDML.FUNC_goBackToMenu(1);      // leave this function and go a layer back
  }
}


// *********************************************************************
void mFunc_goToRootMenu(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // go to root and display menu
    LCDML.MENU_goRoot();
  }
}

// *********************************************************************
void mFunc_jumpTo_timer_info(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // Jump to main screen
    if(!LCDML.OTHER_jumpToFunc(mFunc_timer_info))
    {
      // function not found or not callable
      LCDML.MENU_goRoot();
    }
  }
}


// *********************************************************************
void mFunc_para(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {

    char buf[20];
    sprintf (buf, "parameter: %d", param);

    lcd.setCursor(0, 0);
    lcd.print(buf);
    lcd.setCursor(0, 1);
    lcd.print(F("press any key"));
    lcd.setCursor(0, 2);
    lcd.print(F("to leave it"));

    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds
  }

  if(LCDML.FUNC_loop())          // ****** LOOP *********
  {
    // For example
    switch(param)
    {
      case 10:
        // do something
        break;

      case 20:
        // do something
        break;

      case 30:
        // do something
        break;

      default:
        // do nothing
        break;
    }


    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      LCDML.FUNC_goBackToMenu();  // leave this function
    }
  }

  if(LCDML.FUNC_close())        // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}
