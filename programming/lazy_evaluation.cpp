// https://www.foonathan.net/2017/06/lazy-evaluation/

/**
 *
 * template<typename U>
 * T optional<T>::value_or(U&& fallback)
 * {
 *  if (has_value()) return value();
 *  return static_cast<T>(std::forward<U>(fallback));
 * }
 *
 * auto result = opt.value_or(foo())
 *
 * foo() should only be called if the result is needed
 */

// [use macro]: macos will not evaluate but only past it
// decay_t: the purpose of type decay is to extract the POT
#define VALUE_OR(opt, fallback)                         \
  [&](const auto& optional) \{                          \
    if (optional.has_value()) return optional.value();  \
    using T = std::decay_t<decltype(optional.value())>; \
    return static_cast<T>(fallback);                    \
  }                                                     \
  (opt) \