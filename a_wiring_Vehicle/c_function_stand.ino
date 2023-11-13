

//대기 함수

int Stand() {

  lcd.clear();
  LCD_print_S("sen1:      ", 4, 0); 
  LCD_print_S("sen2:      ", 4, 1); 


  unsigned long Start_Wait_t = millis(), R1_time, R2_time;

  bool ck1 = false, ck2 = false;

  while ( ((millis() - Start_Wait_t) < 5400000 ) && (ck1 == false || ck2 == false) ) {

    
    FSR_Value1 = analogRead(FSRsensor1);
    FSR_Value2 = analogRead(FSRsensor2);

    if (ck1 == false && FSR_Value1 > 300) {
      //식판이 처을 올라간 순간 시간 기록
      if (P1.get_Status() == false) R1_time = millis();

      LCD_print_S("sen1:"+String(FSR_Value1), 4, 0); 

      //디버깅용 시리얼 모니터 출력
      Moniter.println("FSR_Value1 : "+ String(FSR_Value1));///////////
        
      P1.set_Status(true);

      if (millis() - R1_time > 3000) {
        //3초이상 식판이 압력센서에 감지 된 상황

        web.print("stand:"+String(P1.get_Room())+":"+P1.get_Code()+":\n");
        ck1 = true;
        LCD_print_S("sen1:OK   ", 4, 0); 

        digitalWrite(Led1, HIGH);

      }
    } else if (ck1 == false) {

      P1.set_Status(false);
      LCD_print_S("sen1:   ", 4, 0); 
    }

    if (ck2 == false && FSR_Value2 > 300) {
      //식판이 처을 올라간 순간 시간 기록
      if (P2.get_Status() == false) R2_time = millis();

      LCD_print_S("sen2:"+String(FSR_Value2), 4, 1); 

      //디버깅용 시리얼 모니터 출력
      Moniter.println("FSR_Value2 : "+ String(FSR_Value2));////////////

      P2.set_Status(true);

      if (millis() - R2_time > 3000) {
        //3초이상 식판이 압력센서에 감지 된 상황

        web.print("stand:"+String(P2.get_Room())+":"+P2.get_Code()+":\n");
        ck2 = true;
        LCD_print_S("sen2:OK   ", 4, 1); 

        digitalWrite(Led2, HIGH);
      }
    } else if (ck2 == false) {
      P2.set_Status(false);
      LCD_print_S("sen2:   ", 4, 0); 

    }

    delay(30);

  }

  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);

  LCD_print_S("Return" , 6, 0, 1); 
  LCD_print_S("completed" , 4, 1); 
  
}