//메인 실행 파일
#include "_define_.h"
#include <LCD_I2C.h>
#include <Keypad.h>

//동작 변수들 변수정의

const byte ROWS = 4;    // 행(rows) 개수
const byte COLS = 4;    // 열(columns) 개수
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {52, 50, 48, 46};   // R1, R2, R3, R4 단자가 연결된 아두이노 핀 번호
byte colPins[COLS] = {53, 51, 49, 47};   // C1, C2, C3, C4 단자가 연결된 아두이노 핀 번호

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according

uint8_t ho[8] =
{
    0b00100,
    0b11111,
    0b00000,
    0b01110,
    0b10001,
    0b01110,
    0b00100,
    0b11111,
};

// LED D3, D4 설정
const int Led1 = 3; 
const int Led2 = 4;

space P1 = space(1);
space P2 = space(2);

// 압력센서 A0, A1 설정
const int FSRsensor1 = A0;  
const int FSRsensor2 = A1;

//압력센서 측정값 저장 변수 설정
int FSR_Value1;                         
int FSR_Value2;

String cmd, func_cmd;
int cmd_len, func_num;
unsigned long wake_t;
bool Keypad_Enable = false, Wake_status = false; 
char keyPressed, buf[4];

void setup() {

  delay(1000);

  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);


  lcd.begin();
  lcd.backlight();
  lcd.createChar(0, ho);

  Start();
  
}

//기본적으로 대기모드
// 키패드 입력 감지 -> 키패드 동작 입력값 버퍼에 저장하면서 출력
// 엔터누를시 load메세지 웹전송
// 지우기누를시 버퍼 비움 / 일정시간 지날시 버퍼 비움
// 



//임의로 문자열의 각 정보는 :를 기준으로 구분한다 가정
// ex : 1번 공간에 적재 환자 코드는 XX -> (기능번호/적재) : (적재공간/1번) : (환자코드/XX) : (리얼타임)


void loop() {

  //슬립모드일 경우 Wake_status는 false상태로 
  //이때는 창고에서 대기중인 상태
  //식판 적재를 위한 키패드 입력으로만 깨어나는 상태 
  //한번 깨어나면 특정 조건을 만족할 때까지 키패드는 작동되지 않는다.
  if(Wake_status == false){
    keyPressed = keypad.getKey();
    if(keyPressed != NO_KEY){
      Wake_up();
      room_input();
    }
  }
  else{

    if(Serial.available()){
      
      cmd = Serial.readString();

      Serial.println(cmd + "<---- 입력 받은 문자열");

      cmd_len =cmd.length(); 
      func_num = cmd.indexOf(":");
      func_cmd = cmd.substring(0,func_num);

      Serial.println(func_cmd + "<---- 기능 코드");

      if(func_cmd == "load"){
        //적재 함수 호출
        Load(cmd.substring(func_num+1,cmd_len), func_cmd.length());
      }
      else if(func_cmd == "delivery"){
        //배달 함수 호출
        Delivery(cmd.substring(func_num+1,cmd_len), func_cmd.length());
      }
      else if(func_cmd == "stand"){
        //대기 함수 호출
        Stand();
      }
    }
  }
  
}









