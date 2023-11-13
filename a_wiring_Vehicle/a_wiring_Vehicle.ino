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
  { '*', '7', '4', '1' },
  { '0', '8', '5', '2' },
  { '#', '9', '6', '3' },
  { 'D', 'C', 'B', 'A' }
};

//byte rowPins[ROWS] = { 45, 43, 41, 39 };  // R1, R2, R3, R4 단자가 연결된 아두이노 핀 번호
//byte colPins[COLS] = { 47, 49, 51, 53 };  // C1, C2, C3, C4 단자가 연결된 아두이노 핀 번호

byte rowPins[ROWS] = { 45, 43, 41, 39 };  // R1, R2, R3, R4 단자가 연결된 아두이노 핀 번호
byte colPins[COLS] = { 47, 49, 51, 53 };  // C1, C2, C3, C4 단자가 연결된 아두이노 핀 번호

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


//a미리 설정된 룸 목록
int settingRoom[] = {201, 202, 203,204, 205};

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
unsigned long wake_t, cmd_prt_t, Lcd_cl_t; //rl
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

//임의로 문자열의 각 정보는 :를 기준으로 구분한다 가정
// ex : 1번 공간에 적재 환자 코드는 XX -> (기능번호/적재) : (적재공간/1번) : (환자코드/XX) : (리얼타임)

void loop() {

  //슬립모드일 경우 Wake_status는 false상태로
  //이때는 창고에서 대기중인 상태
  //식판 적재를 위한 키패드 입력으로만 깨어나는 상태
  //한번 깨어나면 특정 조건을 만족할 때까지 키패드는 작동되지 않는다.
  if (Wake_status == false) {

    //키패드 입력을 통해 WakeUp
    keyPressed = keypad.getKey();
    if (keyPressed != NO_KEY) {

      lcd.backlight();
      room = room_input();

      if(room > 0){
        
        //시리얼 통신 전에 들어왔을수 있는 시리얼 버퍼 비우기
        reset_serialbuff();
        
        //시리얼1으로 호실 적재 정보 요청
        //리시브 받은 정보를 내부 변수에 저장
        send = send + "Roomnumber" + ":" + String(room)+"\n";
        web.print(send);
        lcd.clear();
        Wake_status = true;
      }
      else if (room == -1){
        //다시 슬립 모드로 돌아가는 동작
        millis_reset();
        Sleep();
      }
      
    }

    //시리얼 입력을 통해 WakeUp
    //이 경우 input_Room 시퀴스를 건너뛰고 바로 동작 상태로 전환
    if(Moniter.available() || ras_ros.available()){
      String n = ras_ros.readString();
      //String n = ras_ros.readString();
      if(n == "%"){
        lcd.backlight();
        reset_serialbuff();
        lcd.clear();
        Wake_status = true;
        lcd.setCursor(4, 0);
        lcd.print("standby!");
      }
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


      //디버깅용 시리얼 모니터 출력
      //Moniter.println(cmd);

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
        //슬립모드 돌입 알리기
      }
      cmd.remove(cmd.length());
    }
  }
  delay(50);
}

