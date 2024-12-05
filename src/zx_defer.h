#ifndef ZX_DEFER_H
#define ZX_DEFER_H

#include <utility>
#include <assert.h>

namespace zx::internal {
template <typename t_callable> class deferred_t {
public:
    deferred_t(t_callable &&func)
        : m_func{std::forward<t_callable>(func)}
    {
    }

    ~deferred_t()
    {
        m_func();
    }

    deferred_t(deferred_t<t_callable> &&) = delete;
    deferred_t(const deferred_t<t_callable> &) = delete;
    deferred_t<t_callable> &operator=(const deferred_t<t_callable> &) = delete;
    deferred_t<t_callable> &operator=(deferred_t<t_callable> &&) = delete;

private:
    t_callable m_func;
};
} // namespace zx::internal

#define ZX_DEFER_CONCATENATE_IMPL(s1, s2) s1##s2
#define ZX_DEFER_CONCATENATE(s1, s2) ZX_DEFER_CONCATENATE_IMPL(s1, s2)

#define ZX_DEFER_ANONYMOUS_VARIABLE(str) ZX_DEFER_CONCATENATE(str, __COUNTER__)

#define zx_defer(code)                                                                   \
    [[maybe_unused]] const auto ZX_DEFER_ANONYMOUS_VARIABLE(defer_) =                    \
        zx::internal::deferred_t([&]() {                                                 \
            code                                                                         \
        })

#endif
