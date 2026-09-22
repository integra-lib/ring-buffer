#pragma once
#include <array>
#include <atomic>
#include <cstddef>

namespace integra
{

/// @brief Fixed-size ring buffer
///
/// Allocates nothing: the storage is a member std::array. A Push into a full
/// buffer drops the value.
///
/// @warning Not thread safe. Push and Pop must not run concurrently, in
/// particular not from an interrupt and a task at the same time.
template<class T, std::size_t SIZE>
class RingBuffer
{
public:
    RingBuffer()                             = default;
    RingBuffer(const RingBuffer&)            = delete;
    RingBuffer(RingBuffer&&)                 = delete;
    ~RingBuffer()                            = default;
    RingBuffer& operator=(const RingBuffer&) = delete;
    RingBuffer& operator=(RingBuffer&&)      = delete;

    void Push(const T& value)
    {
        if (m_size < SIZE)
        {
            ++m_size;
            *m_w++ = value;
            if (m_w == m_buf.end())
            {
                m_w = m_buf.begin();
            }
        }
    }

    [[nodiscard]] bool Pop(T& value)
    {
        bool ret = false;
        if (m_size != 0)
        {
            --m_size;
            value = *m_r++;
            ret   = true;
        }
        if (m_r == m_buf.end())
        {
            m_r = m_buf.begin();
        }
        return ret;
    }

    void Clear()
    {
        m_r = m_w = m_buf.begin();
        m_size    = 0;
    }

    [[nodiscard]] bool IsEmpty() const
    {
        return m_size == 0;
    }

private:
    using ArrayType = std::array<T, SIZE>;
    ArrayType m_buf{};
    ArrayType::iterator m_r{m_buf.begin()};
    ArrayType::iterator m_w{m_buf.begin()};
    std::atomic<std::size_t> m_size{};
};

} // namespace integra
