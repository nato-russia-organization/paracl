#include <location/locationRange.hpp>

namespace paracl {
namespace location_namespace {

std::ostream &operator<<(std::ostream &os, const LocationRange &loc) {
  os << "From: (" << loc.begin.line << ", " << loc.begin.column << "); "
     << "To: (" << loc.end.line << ", " << loc.end.column << ")";
  return os;
}

} // namespace location_namespace
} // namespace paracl
