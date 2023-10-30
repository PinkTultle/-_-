//메인 실행 파일
#include "_define_.h"

//동작 변수들 변수정의

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


void setup() {

  delay(1000);

  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  
  Serial.begin(9600);

  Start();
  
}

//임의로 문자열의 각 정보는 :를 기준으로 구분한다 가정
// ex : 1번 공간에 적재 환자 코드는 XX -> (기능번호/적재) : (적재공간/1번) : (환자코드/XX) : (리얼타임)


void loop() {

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









