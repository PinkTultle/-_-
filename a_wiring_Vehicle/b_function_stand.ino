

//대기 함수

int Stand() {

  Serial.println("대기 함수 호출 성공!");

  unsigned long Start_Wait_t = millis(), R1_time, R2_time;

  bool ck1 = false, ck2 = false;

  while ( ((millis() - Start_Wait_t) < 5400000 ) && (ck1 == false || ck2 == false) ) {

    
    FSR_Value1 = analogRead(FSRsensor1);
    FSR_Value2 = analogRead(FSRsensor2);

    Serial.print("압력 센서 측정값 >> 1번 센서 : ");
    Serial.print(FSR_Value1);
    Serial.print("2번 센서 : ");
    Serial.println(FSR_Value2);


    if (ck1 == false && FSR_Value1 > 600) {
      if (P1.get_Status() == false) R1_time = millis();
      
      Serial.println("1번 센서 인식");
  
      P1.set_Status(true);

      if (millis() - R1_time > 3000) {
        //3초이상 식판이 압력센서에 감지 된 상황
        Serial.println("반납 확인!!");
    
        P1.set_Et(millis());
        ck1 = true;
      }
    } else if (ck1 == false) {

      Serial.println("반납 X!!");
    
      P1.set_Status(false);
    }

    if (ck2 == false && FSR_Value2 > 600) {
      if (P2.get_Status() == false) R2_time = millis();

      Serial.println("2번 센서 인식");


      P2.set_Status(true);

      if (millis() - R2_time > 3000) {
        //3초이상 식판이 압력센서에 감지 된 상황
        Serial.println("반납 확인!!");

        P2.set_Et(millis());
        ck2 = true;
      }
    } else if (ck2 == false) {

      Serial.println("반납 X!!");

      P2.set_Status(false);
    }

    /*
    //대기 함수 종료 테스트 위한 if문
    //3초 대기후 ck1,ck2를 true로 바꿔 함수 종료 유도
    if((millis() - Start_Wait_t) > 3000 ){
      ck1 = true;
      ck2 = true;
    }*/

  }


  Serial.println("대기 함수 종료");

}