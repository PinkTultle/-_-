
//기기가 대기 상태에서 동작을 시작할때 작동할 코드

void Wake_up(){

  wake_t = millis();
  Wake_status = true;

  while(millis() - wake_t > 2500){

    if(millis() - wake_t > 1000)
      LCD_print("대기모드 해제!! 병실을 입력하세요", 10);
    else if(millis() - wake_t > 1500)
      lcd.clear();
    else 
      LCD_print("대기모드 해제!! 병실을 입력하세요", 10);
  }
  lcd.clear();
}

//주의 내부 클럭 초기화 함수로 주의해서 사용
void millis_reset(){

  timer0_millis = 0;

}