

//대기 함수

int Stand() {

  unsigned long Start_Wait_t = millis(), R1_time, R2_time;

  bool ck1 = false, ck2 = false;

  while ( ((millis() - Start_Wait_t) < 5400000 ) && (ck1 == false || ck2 == false) ) {

    
    FSR_Value1 = analogRead(FSRsensor1);
    FSR_Value2 = analogRead(FSRsensor2);

    if (ck1 == false && FSR_Value1 > 600) {
      //식판이 처을 올라간 순간 시간 기록
      if (P1.get_Status() == false) R1_time = millis();
        
      P1.set_Status(true);

      if (millis() - R1_time > 3000) {
        //3초이상 식판이 압력센서에 감지 된 상황
    
        P1.set_Et(millis());

        Moniter.print("stand:"+String(P1.get_Room())+":"+P1.get_Code()+":"+String(P1.mealtime(2)));
        ck1 = true;
      }
    } else if (ck1 == false) {

      P1.set_Status(false);
    }

    if (ck2 == false && FSR_Value2 > 600) {
      //식판이 처을 올라간 순간 시간 기록
      if (P2.get_Status() == false) R2_time = millis();

      P2.set_Status(true);

      if (millis() - R2_time > 3000) {
        //3초이상 식판이 압력센서에 감지 된 상황
        P2.set_Et(millis());

        Moniter.print("stand:"+String(P1.get_Room())+":"+P1.get_Code()+":"+String(P1.mealtime(2)));
        ck2 = true;
      }
    } else if (ck2 == false) {
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
}