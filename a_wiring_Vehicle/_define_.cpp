#include "_define_.h"

//생성자
space::space(int r) {
  status = false;
  this->room = r;
  code = "";
}

//설정자, 접근자 구현
String space::get_Code() {
  return code;
}
bool space::get_Status() {
  return status;
}
int space::get_Room() {
  return this->room;
}


void space::set_Code(String c) {
  code = c;
}
void space::set_Status(bool s) {
  status = s;
}
void space::set_Room(int r) {
  this->room = r;
}

void space::set_Space(String c, bool sta) {
  status = sta;
  code = c;
}


void space::init_space() {
  code.remove(code.length());
  status = false;
}