#include "_define_.h"

//생성자
space::space(){ space(-1);  }

space::space(int r){ space(" ", r);  }

space::space(String c, int r){
    code = c;
    room = r;
    E_time = 0;
    S_time = 0;
    L_time = 0;
    Real_time = 0;
    status = false;
}


//설정자, 접근자 구현
String space::get_Code(){ return code; }
unsigned long space::get_St()  { return S_time;  }
unsigned long space::get_Et()  { return E_time;  }
unsigned long space::get_Lt()  { return L_time;  }
unsigned long space::get_Rt()  { return Real_time;  }
bool space::get_Status() { return status; }
int space::get_Room() { return room;  }


void space::set_Code(String c) { code = c;  }
void space::set_St(unsigned long St)  { S_time = St;  }
void space::set_Et(unsigned long Et)  { E_time = Et;  }
void space::set_Lt(unsigned long Lt)  { L_time = Lt;  }
void space::set_Rt(unsigned long Rt)  { Real_time = Rt;  }
void space::set_Status(bool s)  { status = s; }
void space::set_Room(int r) { room = r;  }

void space::set_Space(String c, unsigned long Lt, unsigned long Rt){
  code = c;
  S_time = 0;
  E_time = 0;
  L_time = Lt;
  Real_time = Rt;
}

//식사 시간 반환
unsigned long space::mealtime()  { return E_time - S_time;}


//객체 정보 출력 함수
void space::show(){
  Serial.println("적재함 정보 출력");
  Serial.print(room);
  Serial.println("번 적재함 환자 코드 : " + code);
  Serial.println("식판을 받은 시간 : " + S_time);
  Serial.println();
  
}