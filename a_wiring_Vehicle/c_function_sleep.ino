void Sleep(){

  lcd.clear();
  LCD_print_S("Sleep Mode!", 2, 1);
  delay(2000);

  
  //대기모드 진입 전 버퍼 비우기
  reset_serialbuff();

  Wake_status = false;
  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
  lcd.clear();
  lcd.noBacklight();

  P1.init_space();
  P2.init_space();

}

void reset_serialbuff(){

  while(Moniter.available() > 0){
    Moniter.read();
  }
  while(web.available() > 0){
    web.read();
  }
  while(ras_ros.available() > 0){
    ras_ros.read();
  }

}

//주의 내부 클럭 초기화 함수로 주의해서 사용
void millis_reset(){

  timer0_millis = 0;

}