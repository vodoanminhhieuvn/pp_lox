#pragma once

namespace wlox::Types {
struct Uncopyable {
  explicit Uncopyable() = default;
  virtual ~Uncopyable() = default;
  Uncopyable(const Uncopyable &) = delete;
  auto operator=(const Uncopyable &) -> Uncopyable & = delete;
  Uncopyable(Uncopyable &&) = delete;
  auto operator=(Uncopyable &&) -> Uncopyable & = delete;
};
} // namespace wlox::Types
