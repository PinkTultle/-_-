//wiring_Vehicle.ino의 함수 구현 파일

//압력센서 동작 확인 함수
void Pressure_test() {

  FSR_Value1 = analogRead(FSRsensor1);
  FSR_Value1 = map(FSR_Value1, 0, 1023, 0, 255);

  FSR_Value2 = analogRead(FSRsensor2);
  FSR_Value2 = map(FSR_Value2, 0, 1023, 0, 255);

  Serial.print("압력센서 측정 테스트\n센서1 : ");
  Serial.print(FSR_Value1);
  Serial.print("\n센서2 : ");
  Serial.println(FSR_Value2);
}

void Start() {

  //LED 동작 체크
  digitalWrite(Led1, HIGH);
  delay(300);
  digitalWrite(Led2, HIGH);
  delay(300);

  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
  delay(100);

  //적재 공간 객체 생성 확인

  //임의의 환자 코드 설정
  P1.set_Code("P234");
  P2.set_Code("P567");
  P1.set_Room(1);
  P2.set_Room(2);

  P1.show();

  P2.show();

  delay(300);

  Pressure_test();
}

//적재 함수
//인자 값 load_cmd의 구성 >> (적재공간/1번) : (환자코드/XX) : (리얼타임)
//문자열에서 필요 데이터 추출
//문자 열 인덱스
//적재 공간 - num
//적재 공간 코드 추출을 위한 인덱스 - Sp_num
//환자 코드 추출을 위한 인덱스 - P_num
//리얼 타임 추출을 위한 인덱스 - T_num
//환자 코드 - code
//환자 코드 + 리얼타임 - code_str
//적재시 아두이노 클락시간 - Lt
//적재시 리얼 타임 - Rt
void Load(String load_cmd, int len) {

  ///////////////////////////////////////////////
  Serial.println("적재 함수 정상 호출");
  Serial.println(load_cmd + " <----------적재 함수 내 전송받은 문자열");
  ///////////////////////////////////////////////


  int num, Sp_num, P_num, T_num;
  unsigned long Lt = millis(), Rt;
  String code, code_str;


  //적재 공간 추출
  Sp_num = load_cmd.indexOf(":");
  num = load_cmd.substring(0, Sp_num).toInt();

  ///////////////////////////////////////////////
  Serial.print(num);
  Serial.println(" <---- 공간 코드");
  ///////////////////////////////////////////////

  //환자 코드 추출
  P_num = load_cmd.indexOf(":", Sp_num + 1);
  T_num = load_cmd.indexOf(":", P_num + 1);
  code = load_cmd.substring(Sp_num + 1, P_num);
  Rt = load_cmd.substring(P_num + 1, T_num).toInt();

  //////////////////////////////////////////////
  Serial.print(Rt);
  Serial.println(" <---- 리얼 타임");
  Serial.println(code + " <---- 환자 코드");
  //////////////////////////////////////////////

  //적재 공간 1 세팅
  if (num == 1) {
    ///////////////////////////////////////////////
    Serial.println("적재 1번 호출");
    ///////////////////////////////////////////////

    P1.set_Space(code, Lt, Rt);
    P1.set_Status(true);
  }

  //적재 공간 2 세팅
  else if (num == 2) {
    ///////////////////////////////////////////////
    Serial.println("적재 2번 호출");
    ///////////////////////////////////////////////

    P2.set_Space(code, Lt, Rt);
    P2.set_Status(true);

  } else {
    Serial.print("적재 데이터 이상!!");
  }
}



