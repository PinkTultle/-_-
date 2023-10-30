
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
      
      //지우기 버튼 : 버퍼 비우고 인덱스 및 LCD 초기화
      if(keyPressed == 'B'){
        lcd.clear();
        lcd.setCursor(10, 0);
        lcd.write(ho);
        index = 0;

        buff[0] = null;
        buff[1] = null;
        buff[2] = null;
        

        continue;
      }

      //엔터버튼
      if(keyPressed = 'C'){
        //버퍼 값을 코드로 만드는 함수 
      }

      //종료 버튼
      if(keyPressed == 'D'){
          //종료시 동작 생각해서 삽입예정

        break;
      }


      
      buff[index] = keyPressed;

      switch(index){
        case 0:
          LCD_pr(keyPressed, 4, 0);
        break;
    
        case 1:
          LCD_pr(keyPressed, 6, 0);
        break;

        case 2:
          LCD_pr(keyPressed, 8, 0);
        break;
      }

      index = (index == 2)? 0 : index+1;

    }  
  }


}
