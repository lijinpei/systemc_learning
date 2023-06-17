#include <iostream>
#include <systemc>

SC_MODULE(MODULE_A){MODULE_A(sc_core::sc_module_name name){
    std::cout << this->name() << ", no SC_CTOR or SC_HAS_PROCESS" << std::endl;
}
}
;

SC_MODULE(MODULE_B1){SC_CTOR(MODULE_B1){SC_METHOD(func_b);
}
void func_b() { std::cout << name() << ", SC_HAS_PROCESS" << std::endl; }
}
;

SC_MODULE(MODULE_B2) {
  SC_HAS_PROCESS(MODULE_B2);
  MODULE_B2(sc_core::sc_module_name name) : sc_core::sc_module(name) {
    SC_METHOD(func_b);
  }
  void func_b() { std::cout << name() << ", SC_HAS_PROCESS" << std::endl; }
};

SC_MODULE(MODULE_C) {
  const int i;
  SC_HAS_PROCESS(MODULE_C);
  MODULE_C(sc_core::sc_module_name name, int i)
      : sc_core::sc_module(name), i(i) {
    SC_METHOD(func_c);
  }
  void func_c() {
    std::cout << name() << ", additional input argument" << std::endl;
  }
};

SC_MODULE(MODULE_D1) {
  SC_CTOR(MODULE_D1);
  void func_d() {
    std::cout << this->name()
              << ", SC_TOR inside header, construction defined outside header"
              << std::endl;
  }
};

SC_MODULE(MODULE_D2) {
  SC_HAS_PROCESS(MODULE_D2);
  MODULE_D2(sc_core::sc_module_name);
  void func_d() {
    std::cout << this->name() << ", SC_CTOR inside header, CANNOT use SC_TOR"
              << std::endl;
  }
};

SC_MODULE(MODULE_E) {
  MODULE_E(sc_core::sc_module_name name);
  void func_e() {
    std::cout << this->name()
              << ", SC_HAS_PROCESS outside header, CANNOT use SC_CTOR"
              << std::endl;
  }
};
