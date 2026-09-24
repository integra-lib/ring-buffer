#include <gtest/gtest.h>

#include <cstdint>
#include <hwlib/data_structures/ring_buffer.hpp>

namespace
{

TEST(RingBufferTest, IsEmptyAfterConstruction)
{
    const hwlib::data_structures::RingBuffer<std::uint16_t, 4> buffer;
    EXPECT_TRUE(buffer.IsEmpty());
}

TEST(RingBufferTest, PopReturnsFalseWhenEmpty)
{
    hwlib::data_structures::RingBuffer<std::uint16_t, 4> buffer;
    std::uint16_t value{};
    EXPECT_FALSE(buffer.Pop(value));
}

TEST(RingBufferTest, PopsInPushOrder)
{
    hwlib::data_structures::RingBuffer<std::uint16_t, 4> buffer;
    buffer.Push(1U);
    buffer.Push(2U);
    buffer.Push(3U);

    std::uint16_t value{};
    ASSERT_TRUE(buffer.Pop(value));
    EXPECT_EQ(value, 1U);
    ASSERT_TRUE(buffer.Pop(value));
    EXPECT_EQ(value, 2U);
    ASSERT_TRUE(buffer.Pop(value));
    EXPECT_EQ(value, 3U);
    EXPECT_TRUE(buffer.IsEmpty());
}

TEST(RingBufferTest, WrapsAroundTheStorage)
{
    hwlib::data_structures::RingBuffer<std::uint16_t, 3> buffer;
    buffer.Push(1U);
    buffer.Push(2U);
    buffer.Push(3U);

    std::uint16_t value{};
    ASSERT_TRUE(buffer.Pop(value));
    ASSERT_TRUE(buffer.Pop(value));
    buffer.Push(4U);
    buffer.Push(5U);

    ASSERT_TRUE(buffer.Pop(value));
    EXPECT_EQ(value, 3U);
    ASSERT_TRUE(buffer.Pop(value));
    EXPECT_EQ(value, 4U);
    ASSERT_TRUE(buffer.Pop(value));
    EXPECT_EQ(value, 5U);
}

TEST(RingBufferTest, DropsValuePushedIntoFullBuffer)
{
    hwlib::data_structures::RingBuffer<std::uint16_t, 2> buffer;
    buffer.Push(1U);
    buffer.Push(2U);
    buffer.Push(3U);

    std::uint16_t value{};
    ASSERT_TRUE(buffer.Pop(value));
    EXPECT_EQ(value, 1U);
    ASSERT_TRUE(buffer.Pop(value));
    EXPECT_EQ(value, 2U);
    EXPECT_FALSE(buffer.Pop(value));
}

TEST(RingBufferTest, ClearDiscardsContent)
{
    hwlib::data_structures::RingBuffer<std::uint16_t, 4> buffer;
    buffer.Push(1U);
    buffer.Push(2U);
    buffer.Clear();

    EXPECT_TRUE(buffer.IsEmpty());
    std::uint16_t value{};
    EXPECT_FALSE(buffer.Pop(value));
}

} // namespace
