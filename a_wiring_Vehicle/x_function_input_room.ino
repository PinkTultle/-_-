
//키패드를 통해 병실 번호을 입력 받는 함수
//키패드의 종료 버튼을 누르거나,
//병실 번호를 입력받기 전에 종료되지 않는다.

void room_input(){

  int index = 0;

  lcd.setCursor(10, 0);
  lcd.write(ho);

  while(1){
    keyPressed = keypad.getKey();  
    if(keyPressed != NO_KEY)  
    {  
      
      buff[index] = keyPressed;
      switch(index){
        case 0:
          LCD_print_C(keyPressed, 4, 0){
        break;
    
        case 1:
          LCD_print_C(keyPressed, 6, 0)
        break;

        case 2:
          LCD_print_C(keyPressed, 8, 0)
        break;
      }

      index = (index == 2)? 0 : index+1;

      }  
    }
  }
}