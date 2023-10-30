
//배달 함수
//인자 값 deli_cmd의 구성 >> (배달시 해당 칸 사용 X) : (환자코드/XX) : (리얼타임)
//문자열에서 필요 데이터 추출
//문자 열 인덱스
//적재 공간 코드 추출을 위한 인덱스 - Sp_num
//환자 코드 추출을 위한 인덱스 - P_num
//리얼 타임 추출을 위한 인덱스 - T_num
//환자 코드 - code
//환자 코드 + 리얼타임 - code_str
//환자한테 도착시 아두이노 클락시간 - Lt
//배달시 리얼 타임 - Rt

int Delivery(String deli_cmd, int len){

  ///////////////////////////////////////////////
  Serial.println("배달 함수 정상 호출");
  Serial.println(deli_cmd + " <----------배달 함수 내 전송받은 문자열");
  ///////////////////////////////////////////////


  int num, Sp_num, P_num, T_num;
  unsigned long Lt = millis(), Rt;
  String code, code_str;


  //적재 공간 추출
  Sp_num = deli_cmd.indexOf(":");

  //환자 코드 및 리얼 타임 추출
  P_num = deli_cmd.indexOf(":", Sp_num + 1);
  T_num = deli_cmd.indexOf(":", P_num + 1);
  code = deli_cmd.substring(Sp_num + 1, P_num);
  Rt = deli_cmd.substring(P_num + 1, T_num).toInt();

  //////////////////////////////////////////////
  Serial.print(Rt);
  Serial.println(" <---- 리얼 타임");
  Serial.println(code + " <---- 환자 코드");
  //////////////////////////////////////////////

  //환자 1 배달
  if (P1.get_Code().equals(code)) {
    ///////////////////////////////////////////////
    Serial.println("배달 1번 호출");
    ///////////////////////////////////////////////

    //압력센서 동작 및 LED ON / 기다리는 함수 호출
    digitalWrite(Led1, HIGH);
    feeding_Stand(P1, 1);

  }

  //적재 공간 2 세팅
  else if (P2.get_Code().equals(code)) {
    ///////////////////////////////////////////////
    Serial.println("배달 2번 호출");
    ///////////////////////////////////////////////

    //압력센서 동작 및 LED ON / 기다리는 함수 호출
    digitalWrite(Led2, HIGH);
    feeding_Stand(P2, 2);

  } else {
    Serial.print("배달 데이터 이상!!");
  }

  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
}


int feeding_Stand(space p, int fsr){
  
  Serial.println("압력센서 호출 정상");
  unsigned long Now = millis(), Wait = 0, check = 0;
  int var, sensor;

  if(fsr == 1) sensor = FSRsensor1;
  if(fsr == 2) sensor = FSRsensor2;
  
  while(1){
    
    var = analogRead(sensor);     // 센서값을 아나로그로 읽어 value 변수에 저장
    Serial.println(var);
    Wait = millis() - Now;

    //받지 않고 대기 시간이 지났을경우
    if(var > 400 && Wait > 300000){
      p.set_Status(true);

      return -1;
    } //식판을 받았을 때
    else if(var < 400){
      if(p.get_Status() == true){
        p.set_Status(false);
        check = millis();
      }
      
      //식판을 꺼내고 3초간 유지해야 식판을 꺼낸것으로 인식
      if( (millis() - check) > 3000) {
        Serial.print(millis());
        Serial.print(" : ");
        Serial.println(/*millis() - */check);
        
        Serial.println("성공!");
        p.set_St(millis());
        return 1;
      }
    }
  }
}




