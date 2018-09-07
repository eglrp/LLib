#include <iostream>
#include "../Mat/mat_header.h"
#include "../../Utility/test.h"

int test_id = 1;

int main(int argc, char **argv)
{
  LOG("Start Testing mat22!");
  LOG("static funtion Testing!");
  mat22i m1(0,0,0,0);
  std::cout << m1 << std::endl;
  return 0;
}
