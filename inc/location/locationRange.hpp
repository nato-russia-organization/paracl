#pragma once

#include <cstddef>
#include <ostream>

namespace paracl {
namespace location_namespace {

struct Location final {
  size_t line = 0;
  size_t column = 0;
};

struct LocationRange final {
  Location begin;
  Location end;

  void step() { begin = end; }

  void columns(size_t width) { end.column += width; }

  void lines(size_t len) { end.line += len; }
};

std::ostream &operator<<(std::ostream &os, const LocationRange &loc);

} // namespace location_namespace
} // namespace paracl
