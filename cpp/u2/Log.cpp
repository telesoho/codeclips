#include "Log.h"
using namespace u2;
std::vector<std::shared_ptr<std::ostream>> Log::_os;
int Log::_dump_level = 3;