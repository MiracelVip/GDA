void b_start() {
  Serial.println("b_start");
   LCDML.OTHER_jumpToFunc(automatic_filling);
} // longPress1

void bottle_full() {
  full = true;
  Serial.println("Bottle full");
  detachInterrupt(digitalPinToInterrupt(sensor_bottle));
}

void b_stop() {
    Serial.println("STOP BUTTON");
    digitalWrite(ventil_co2, LOW);
    digitalWrite(ventil_bier, LOW);
    digitalWrite(ventil_co2_ab_l, LOW);
    digitalWrite(ventil_co2_ab_s, LOW);
  LCDML.FUNC_goBackToMenu();
}

void b_manualFill(){
  Serial.println("b_manualFilling");
  LCDML.OTHER_jumpToFunc(manual_fill);
 // LCDML.OTHER_jumpToFunc(mFunc_information);
}

void b_manualPressure(){
  Serial.println("b_manualPressure");
  LCDML.OTHER_jumpToFunc(manual_pressure);
  
}

void b_clean(){
  Serial.println("b_clean");
//  LCDML.OTHER_jumpToFunc(manual_Pressure);
  
}
