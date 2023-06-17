#include <iostream>
#include <systemc>

void hello1() { std::cout << "Hello world using approach 1" << std::endl; }

struct HelloWorld : sc_core::sc_module {
  SC_CTOR(HelloWorld) { SC_METHOD(hello2); }

  void hello2(void) {
    std::cout << "Hello world using approach 2" << std::endl;
  }
};

int sc_main(int argc, char* argv[]) {
  hello1();
  HelloWorld hello_world("hello_world");
  sc_core::sc_start();

  return 0;
}
