
/*
  함수 설명
  LCD에 매개변수로 전달할 문자열을 출력하는 함수
  
  파라매터 설명
  String text : LCD에 출력할 문자열
  int cut :
  0 >> 첫 줄에 문자열 전체 출력
  양수 >> cut번째 글자에서 줄바꿈

*/
void LCD_print(String text, int cut){

  lcd.clear();
  int len = text.length(), location;

  if( cut == 0){

    location = ((len % 2) == 0)? (8 - len/2) : (7 - len/2); 

    lcd.setCursor(location, 0);
    lcd.print(text);

  }
  else if(cut > 0){
    String str1, str2;
    location;

    str1 = text.substring(0, cut-1);
    str2 = text.substring(cut, len);

    //첫 번째 줄 출력 
    len = str1.length();
    location = ((len % 2) == 0)? (8 - len/2) : (7 - len/2); 
    lcd.setCursor(location, 0);
    lcd.print(str1);

    //두 번째 줄 출력
    len = str2.length();
    location = ((len % 2) == 0)? (8 - len/2) : (7 - len/2);
    lcd.setCursor(location, 1);
    lcd.print(str2);
  }
}

void LCD_print_S(String text, int col, int row, int cl = 0){
  
  if(cl == 1) lcd.clear();

  lcd.setCursor(col, row);
  lcd.print(text);

}

void LCD_pr(char ch, int col, int row, int cl = 0){

  if(cl == 1) lcd.clear();

  lcd.setCursor(col, row);
  lcd.print(ch);

}

