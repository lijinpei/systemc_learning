#include <systemc>

SC_MODULE(MODULE_A){
    SC_CTOR(MODULE_A){std::cout << name() << " constructor" << std::endl;
}
}
;

struct MODULE_B : sc_core::sc_module {
 public:
  SC_CTOR(MODULE_B) { std::cout << name() << " constructor" << std::endl; }
};

class MODULE_C : public sc_core::sc_module {
 public:
  SC_CTOR(MODULE_C) { std::cout << name() << " constructor" << std::endl; }
};

int sc_main(int argc, char* argv[]) {
  MODULE_A module_a("module_a");
  MODULE_B module_b("module_b");
  MODULE_C module_c("module_c");

  sc_core::sc_start();
  return 0;
}
