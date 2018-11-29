/* ===================================================================== *
 *                                                                       *
 * Dynamic content                                                       *
 *                                                                       *
 * ===================================================================== *
 */

void dyn_para_0(uint8_t line){
  if (line == LCDML.MENU_getCursorPos()){
    if(LCDML.BT_checkAny()){
      if(LCDML.BT_checkLeft()){ g_para_0 += 100;}
      if(LCDML.BT_checkRight()){g_para_0 -= 100;}
    }
  }
  char buf[16];
  sprintf (buf, "t[ms]: %d", g_para_0);
  lcd.setCursor(1, line);
  lcd.print(buf);
}
void dyn_para_2(uint8_t line){
  if (line == LCDML.MENU_getCursorPos()){
    if(LCDML.BT_checkAny()){
      if(LCDML.BT_checkLeft()){ g_para_2 += 100;}
      if(LCDML.BT_checkRight()){g_para_2 -= 100;}
    }
  }
  char buf[16];
  sprintf (buf, "t[ms]: %d", g_para_2);
  lcd.setCursor(1, line);
  lcd.print(buf);
}
void dyn_para_4(uint8_t line){
  if (line == LCDML.MENU_getCursorPos()){
    if(LCDML.BT_checkAny()){
      if(LCDML.BT_checkLeft()){ g_para_4 += 100;}
      if(LCDML.BT_checkRight()){g_para_4 -= 100;}
    }
  }
  char buf[16];
  sprintf (buf, "t[ms]: %d", g_para_4);
  lcd.setCursor(1, line);
  lcd.print(buf);
}
void dyn_para_6(uint8_t line){
  if (line == LCDML.MENU_getCursorPos()){
    if(LCDML.BT_checkAny()){
      if(LCDML.BT_checkLeft()){ g_para_6 += 100;}
      if(LCDML.BT_checkRight()){g_para_6 -= 100;}
    }
  }
  char buf[16];
  sprintf (buf, "t[ms]: %d", g_para_6);
  lcd.setCursor(1, line);
  lcd.print(buf);
}
void dyn_para_8(uint8_t line){
  if (line == LCDML.MENU_getCursorPos()){
    if(LCDML.BT_checkAny()){
      if(LCDML.BT_checkLeft()){ g_para_8 += 100;}
      if(LCDML.BT_checkRight()){g_para_8 -= 100;}
    }
  }
  char buf[16];
  sprintf (buf, "t[ms]: %d", g_para_8);
  lcd.setCursor(1, line);
  lcd.print(buf);
}
void dyn_para_10(uint8_t line){
  if (line == LCDML.MENU_getCursorPos()){
    if(LCDML.BT_checkAny()){
      if(LCDML.BT_checkLeft()){ g_para_10 += 100;}
      if(LCDML.BT_checkRight()){g_para_10 -= 100;}
    }
  }
  char buf[16];
  sprintf (buf, "t[ms]: %d", g_para_10);
  lcd.setCursor(1, line);
  lcd.print(buf);
}
void dyn_para_12(uint8_t line){
  if (line == LCDML.MENU_getCursorPos()){
    if(LCDML.BT_checkAny()){
      if(LCDML.BT_checkLeft()){ g_para_12 += 100;}
      if(LCDML.BT_checkRight()){g_para_12 -= 100;}
    }
  }
  char buf[16];
  sprintf (buf, "t[ms]: %d", g_para_12);
  lcd.setCursor(1, line);
  lcd.print(buf);
}
void dyn_para_14(uint8_t line){
  if (line == LCDML.MENU_getCursorPos()){
    if(LCDML.BT_checkAny()){
      if(LCDML.BT_checkLeft()){ g_para_14 += 100;}
      if(LCDML.BT_checkRight()){g_para_14 -= 100;}
    }
  }
  char buf[16];
  sprintf (buf, "t[ms]: %d", g_para_14);
  lcd.setCursor(1, line);
  lcd.print(buf);
}
