#include "debug_print.h"

namespace wlox::ErrorAndDebug {
void debugPrint(const std::string &str) {
#if _CPPLOX_DEBUG_
  std::cout << str << std::endl;
#endif // CPPLOXDEBUG
}
} // namespace wlox::ErrorAndDebug
