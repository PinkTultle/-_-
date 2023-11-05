
//압력센서 동작 확인 함수
void Pressure_test() {

  FSR_Value1 = analogRead(FSRsensor1);

  FSR_Value2 = analogRead(FSRsensor2);
/*
  Moniter.print("압력센서 측정 테스트\n센서1 : ");
  Moniter.print(FSR_Value1);
  Moniter.print("\n센서2 : ");
  Moniter.println(FSR_Value2);
  */
}


void Start() {

  P1.init_space();
  P2.init_space();

/*
  P1.show();
  P2.show();
*/
  Pressure_test();
}