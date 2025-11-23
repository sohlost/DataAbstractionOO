#pragma once
#include <concepts>
#include <cstddef>

namespace ds {

template<typename T>
concept Container = requires(const T& c) {
    { c.size() } -> std::convertible_to<std::size_t>;
    { c.empty() } -> std::convertible_to<bool>;
};

template<typename S, typename T>
concept BackPushable = requires(S& s, const T& val) { s.push_back(val); };

template<typename S>
concept BackPoppable = requires(S& s) { s.pop_back(); };

template<typename S, typename T>
concept BackAccessible = requires(const S& s) { { s.back() } -> std::convertible_to<const T&>; };

template<typename S, typename T>
concept FrontPushable = requires(S& s, const T& val) { s.push_front(val); };

template<typename S>
concept FrontPoppable = requires(S& s) { s.pop_front(); };

template<typename S, typename T>
concept FrontAccessible = requires(const S& s) { { s.front() } -> std::convertible_to<const T&>; };

template<typename S, typename T>
concept HeapPushable = requires(S& s, const T& val) { s.push(val); };

template<typename S>
concept HeapPoppable = requires(S& s) { s.pop(); };

template<typename S, typename T>
concept HeapAccessible = requires(const S& s) { { s.top() } -> std::convertible_to<const T&>; };

template<typename S, typename T>
concept SequenceStorage = Container<S> && 
                          BackPushable<S, T> && BackPoppable<S> && BackAccessible<S, T> &&
                          FrontPushable<S, T> && FrontPoppable<S> && FrontAccessible<S, T>;

template<typename S, typename T>
concept StackStorage = Container<S> && 
                       BackPushable<S, T> && BackPoppable<S> && BackAccessible<S, T>;

template<typename S, typename T>
concept QueueStorage = Container<S> && 
                       BackPushable<S, T> && FrontPoppable<S> && FrontAccessible<S, T>;
// Note: Queue usually pushes to back and pops from front.

template<typename S, typename T>
concept PriorityQueueStorage = Container<S> && 
                               HeapPushable<S, T> && HeapPoppable<S> && HeapAccessible<S, T>;

} // namespace ds

