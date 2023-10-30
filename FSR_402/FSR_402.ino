int Led = 3;                                         // LED를 3번핀 설정

int FSRsensor = A0;                           // 센서값을 아나로그 A0핀 설정

int value = 0;                                       // loop에서 사용할 변수 설정


void setup() 
{

  pinMode(Led, OUTPUT);                 // 핀모드 LED를 출력으로 설정

  Serial.begin(9600);                           // 시리얼 통신 설정 (보드레이트 9600)

}

void loop() 
{

  value = analogRead(FSRsensor);     // 센서값을 아나로그로 읽어 value 변수에 저장

  Serial.println(value);                           // 센서값을 시리얼 모니터에 출력

  value = map(value, 0, 1023, 0, 255); // value에 저장된 센서값(0~1023)을 PWM값 0~255의 범위로 변환

  analogWrite(Led, value);                    // 변환된 PWM값으로 LED를 켠다 (변하는 값으로 밝기를 조절) 

  delay(1000);                                         // 1초의 딜레이

}