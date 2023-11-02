
//키패드를 통해 병실 번호을 입력 받는 함수
//키패드의 종료 버튼을 누르거나,
//병실 번호를 입력받기 전에 종료되지 않는다.

void room_input(){

  
  lcd.clear();
  int index = 0;
  int room_num;

  reset_input();

  while(1){

    char input = keypad.getKey();

    if(input)  
    {  

      //지우기 버튼 : 버퍼 비우고 인덱스 및 LCD 초기화
      if(input == 'B'){
        reset_input();
        index = 0;
        continue;
      }

      //엔터버튼
      if(input == 'C'){
        //버퍼 값을 코드로 만드는 함수 
        Enter(&room_num);

        if(room_num < 0){
          reset_input();
          LCD_print_S("ERROR!!", 4, 1);
          continue;
        }
        Serial.print("룸 번호 입력 : ");
        Serial.println(room_num);

        LCD_print_S("OKEY!!", 5, 1);

        return  NULL;
      }

      //종료 버튼
      if(input == 'D'){
          //종료시 동작 생각해서 삽입예정

        break;
      }

      if(index == 0){
        reset_input();
      }
      
      buf[index] = input;
      Serial.print("키패드 입력 : ");
      Serial.println(buf[index]);
      

      switch(index){
        case 0:
          LCD_pr(buf[index], 4, 0);
        break;
    
        case 1:
          LCD_pr(buf[index], 6, 0);
        break;

        case 2:
          LCD_pr(buf[index], 8, 0);
        break;
      }

      index = (index == 2)? 0 : index+1;

      

    }  
  }
}


void reset_input(){
  
  lcd.clear();

  LCD_pr('_', 4, 0);
  LCD_pr('_', 6, 0);
  LCD_pr('_', 8, 0);
  LCD_pr(ho, 10, 0);
  
  buf[0] = NULL;
  buf[1] = NULL;
  buf[2] = NULL;

}



//buf에 저장된 값 검사하여 유효 값이면 반환
//유효 값이 아니면 -1 리턴
void Enter(int *room_num){
  
  *room_num = 0;

  for(int i = 0 ;i < 3; i++){
    if(buf[i] < '0' || buf[i] > '9'){
      *room_num = -1;
      break;
    }

    *room_num += (buf[i] - '0');
    
    *room_num = (i < 2) ? *room_num*10 : *room_num; 
  }

}
