#include "_define_.h"

//생성자
space::space() {
  space(0);
}

space::space(int r) {
  space(" ", r);
}

space::space(String c, int r) {
  code = c;
  room = r;
  status = false;
}


//설정자, 접근자 구현
String space::get_Code() {
  return code;
}
bool space::get_Status() {
  return status;
}
int space::get_Room() {
  return room;
}


void space::set_Code(String c) {
  code = c;
}
void space::set_Status(bool s) {
  status = s;
}
void space::set_Room(int r) {
  room = r;
}

void space::set_Space(String c, bool sta) {
  status = sta;
  code = c;
}


void space::init_space() {

  code.remove(code.length());
  status = false;
}