
//기기가 대기 상태에서 동작을 시작할때 작동할 코드

void Wake_up(){

  Wake_status = true;
  wake_t = millis();

  LCD_print("대기모드 해제!! 병실을 입력하세요", 10);

  if(millis() - wake_t > 2000) lcd.clear();
}