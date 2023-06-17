#include "has_process.hpp"

#include <iostream>
#include <systemc>

MODULE_D1::MODULE_D1(sc_core::sc_module_name name) : sc_core::sc_module(name) {
  SC_METHOD(func_d);
}

MODULE_D2::MODULE_D2(sc_core::sc_module_name name) : sc_core::sc_module(name) {
  SC_METHOD(func_d);
}

MODULE_E::MODULE_E(sc_core::sc_module_name name) {
  SC_HAS_PROCESS(MODULE_E);
  SC_METHOD(func_e);
}
