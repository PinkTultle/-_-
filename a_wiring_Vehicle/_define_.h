
//식판 보관 공간에 대한 클래스 정의


#ifndef _define_
#define _define_

//#include "a"
#include "Arduino.h"


/*
환자 클래스 정의 및 프로그램내 사용 변수들 설정
*/

class space {
private:

  //환자 코드, 식사 시작시간 및 반납시간, 적재 시간
  int room;
  String code;
  bool status;


public:

  space(int r);

  //설정자 / 접근자 정의
  String get_Code();
  bool get_Status();
  int get_Room();

  void set_Code(String c);
  void set_Status(bool S);
  void set_Room(int r);

  void set_Space(String c, bool sta);

  //식사 시간 반환
  void init_space();

};

extern space New;



#endif
