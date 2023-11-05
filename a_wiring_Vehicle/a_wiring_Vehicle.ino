//메인 실행 파일
#include "_define_.h"
#include <LCD_I2C.h>
#include <Keypad.h>

//내부 클럭 시간을 변경 할 수 있게하는 코드
extern volatile unsigned long timer0_millis;

//시리얼 통신 포트의 이름 변경
HardwareSerial& Moniter = Serial;
HardwareSerial& web = Serial1;
HardwareSerial& ras_ros = Serial2;

#define Wait_ms 180000


//동작 변수들 변수정의

const byte ROWS = 4;  // 행(rows) 개수
const byte COLS = 4;  // 열(columns) 개수
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = { 52, 50, 48, 46 };  // R1, R2, R3, R4 단자가 연결된 아두이노 핀 번호
byte colPins[COLS] = { 53, 51, 49, 47 };  // C1, C2, C3, C4 단자가 연결된 아두이노 핀 번호

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

LCD_I2C lcd(0x27, 16, 2);  // Default address of most PCF8574 modules, change according

uint8_t ho[8] = {
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
//에러 확인을 위한 LED
const int err_Led = 5;

space P1 = space(1);
space P2 = space(2);

// 압력센서 A0, A1 설정
const int FSRsensor1 = A0;
const int FSRsensor2 = A1;

//압력센서 측정값 저장 변수 설정
int FSR_Value1;
int FSR_Value2;

String cmd, func_cmd, send = "";
int cmd_len, func_num, room;
unsigned long wake_t;
bool Keypad_Enable = false, Wake_status = false;
char keyPressed, buf[4];


void setup() {

  delay(1000);

  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  Moniter.begin(9600);
  web.begin(9600);
  ras_ros.begin(9600);

  lcd.begin();
  lcd.createChar(0, ho);

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
  if (Wake_status == false) {
    lcd.backlight();
    keyPressed = keypad.getKey();
    if (keyPressed != NO_KEY) {
      Wake_up();
      room = room_input();

      if(room > 0){
        
        //시리얼 통신 전에 들어왔을수 있는 시리얼 버퍼 비우기
        reset_serialbuff();
        
        //시리얼1으로 호실 적재 정보 요청
        //리시브 받은 정보를 내부 변수에 저장
        send = send + "Roomnumber" + ":" + String(room)+"\n";
        Moniter.print(send);
      }
      else if (room == -1){
        //다시 슬립 모드로 돌아가는 동작
        millis_reset();
        Sleep();
      }

      lcd.clear();
      Wake_status = true;
    }
  } else {

    if (Moniter.available() || web.available() || ras_ros.available()) {

      if (Moniter.available()) {
        cmd = Moniter.readString();
      } else if (web.available()) {
        cmd = web.readString();
      } else {
        cmd = ras_ros.readString();
      }

      cmd_len = cmd.length();
      func_num = cmd.indexOf(":");
      func_cmd = cmd.substring(0, func_num);

      if (func_cmd == "load") {
        //적재 함수 호출
        Load(cmd.substring(func_num + 1, cmd_len), func_cmd.length());
      } else if (func_cmd == "delivery") {
        //배달 함수 호출
        Delivery(cmd.substring(func_num + 1, cmd_len), func_cmd.length());
      } else if (func_cmd == "stand") {
        //대기 함수 호출
        Stand();
      }else if (func_cmd == "sleep"){
        Sleep();
      }
      else {
        digitalWrite(err_Led, HIGH);
      }
    }
  }
}
