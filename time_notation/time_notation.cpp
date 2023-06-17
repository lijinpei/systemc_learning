#include <systemc>

int sc_main(int argc, char* argv[]) {
  sc_core::sc_report_handler::set_actions("/IEEE_Std_1666/deprecated",
                                          sc_core::SC_DO_NOTHING);
  sc_core::sc_set_time_resolution(1, sc_core::SC_FS);
  sc_core::sc_set_default_time_unit(1, sc_core::SC_SEC);
  std::cout << "1 SEC = "
            << sc_core::sc_time(1, sc_core::SC_SEC).to_default_time_units()
            << " SEC" << std::endl;
  std::cout << "1 MS = "
            << sc_core::sc_time(1, sc_core::SC_MS).to_default_time_units()
            << " SEC" << std::endl;
  std::cout << "1 US = "
            << sc_core::sc_time(1, sc_core::SC_US).to_default_time_units()
            << " SEC" << std::endl;
  std::cout << "1 NS = "
            << sc_core::sc_time(1, sc_core::SC_NS).to_default_time_units()
            << " SEC" << std::endl;
  std::cout << "1 PS = "
            << sc_core::sc_time(1, sc_core::SC_PS).to_default_time_units()
            << " SEC" << std::endl;
  std::cout << "1 FS = "
            << sc_core::sc_time(1, sc_core::SC_FS).to_default_time_units()
            << " SEC" << std::endl;
  sc_start(7261, sc_core::SC_SEC);
  double t = sc_core::sc_time_stamp().to_seconds();
  std::cout << int(t) / 3600 << " hours, " << (int(t) % 3600) / 60
            << " minutes, " << (int(t) % 60) << " seconds" << std::endl;
  return 0;
}
