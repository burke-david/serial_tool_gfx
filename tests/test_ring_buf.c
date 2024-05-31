#include "unity.h"
#include "ring_buf.h"
#include "ring_buf.c"
#include <stdint.h>



/**
 * @brief Set up function that is called before each test case.
 */
void setUp(void)
{

}

/**
 * @brief Tear down function that is called after each test case.
 */
void tearDown(void)
{

}

void test_ring_buf_init(void)
{
    ring_buf_t buf;
    uint8_t buffer[10];
    size_t item_size = sizeof(uint8_t);

    // Test initialization with valid parameters
    ring_buf_init(&buf, buffer, sizeof(buffer), item_size);
    TEST_ASSERT_EQUAL_PTR(buffer, buf.buf);
    TEST_ASSERT_EQUAL(sizeof(buffer), buf.size);
    TEST_ASSERT_EQUAL(item_size, buf.item_size);
    TEST_ASSERT_EQUAL(0, buf.head);
    TEST_ASSERT_EQUAL(0, buf.tail);

    // Test initialization with NULL object
    ring_buf_init(NULL, buffer, sizeof(buffer), item_size);
    // No assertions, just checking for any crashes
}

void test_ring_buf_clear(void)
{
    ring_buf_t buf;
    uint8_t buffer[10];
    size_t item_size = sizeof(uint8_t);

    // Initialize the buffer
    ring_buf_init(&buf, buffer, sizeof(buffer), item_size);

    // Test clearing a non-empty buffer
    buf.head = 5;
    buf.tail = 3;
    ring_buf_clear(&buf);
    TEST_ASSERT_EQUAL(0, buf.head);
    TEST_ASSERT_EQUAL(0, buf.tail);

    // Test clearing an empty buffer
    buf.head = 0;
    buf.tail = 0;
    ring_buf_clear(&buf);
    TEST_ASSERT_EQUAL(0, buf.head);
    TEST_ASSERT_EQUAL(0, buf.tail);

    // Test clearing a NULL buffer
    ring_buf_clear(NULL);
    // No assertions, just checking for any crashes
}

void test_ring_buf_is_empty(void)
{
    ring_buf_t buf;
    uint8_t buffer[10];
    size_t item_size = sizeof(uint8_t);

    // Initialize the buffer
    ring_buf_init(&buf, buffer, sizeof(buffer), item_size);

    // Test an empty buffer
    TEST_ASSERT_TRUE(ring_buf_is_empty(&buf));

    // Test a non-empty buffer
    buf.head = 5;
    buf.tail = 3;
    TEST_ASSERT_FALSE(ring_buf_is_empty(&buf));

    // Test a NULL buffer
    TEST_ASSERT_TRUE(ring_buf_is_empty(NULL));
}

void test_ring_buf_is_full(void)
{
    ring_buf_t buf;
    uint8_t buffer[10];
    size_t item_size = sizeof(uint8_t);

    // Initialize the buffer
    ring_buf_init(&buf, buffer, sizeof(buffer), item_size);

    // Test a non-full buffer
    TEST_ASSERT_FALSE(ring_buf_is_full(&buf));

    // Test a full buffer
    // Fill the buffer
    for (size_t i = 0; i < sizeof(buffer); i++) {
        buffer[i] = 0xAA;
        ring_buf_push(&buf, &buffer[i]);
    }
    TEST_ASSERT_TRUE(ring_buf_is_full(&buf));

    // Test a NULL buffer
    TEST_ASSERT_FALSE(ring_buf_is_full(NULL));
}

void test_ring_buf_push(void)
{
    ring_buf_t buf;
    uint8_t buffer[10];
    size_t item_size = sizeof(uint8_t);
    uint8_t item = 0xAA;

    // Initialize the buffer
    ring_buf_init(&buf, buffer, sizeof(buffer), item_size);

    // Test pushing into a non-full buffer
    TEST_ASSERT_TRUE(ring_buf_push(&buf, &item));
    TEST_ASSERT_EQUAL(1, buf.head);
    TEST_ASSERT_EQUAL(0, buf.tail);
    TEST_ASSERT_EQUAL(item, buffer[0]);

    // Test pushing into a full buffer
    buf.head = 9;
    buf.tail = 0;
    TEST_ASSERT_FALSE(ring_buf_push(&buf, &item));
    TEST_ASSERT_EQUAL(9, buf.head);
    TEST_ASSERT_EQUAL(0, buf.tail);

    // Test pushing into a NULL buffer
    TEST_ASSERT_FALSE(ring_buf_push(NULL, &item));
}

void test_ring_buf_pop(void)
{
    ring_buf_t buf;
    uint8_t buffer[10];
    size_t item_size = sizeof(uint8_t);
    uint8_t item;

    // Initialize the buffer
    ring_buf_init(&buf, buffer, sizeof(buffer), item_size);

    // Test popping from an empty buffer
    TEST_ASSERT_FALSE(ring_buf_pop(&buf, &item));

    // Test popping from a non-empty buffer
    buffer[0] = 0xAA;
    buf.head = 1;
    buf.tail = 0;
    TEST_ASSERT_TRUE(ring_buf_pop(&buf, &item));
    TEST_ASSERT_EQUAL(0xAA, item);
    TEST_ASSERT_EQUAL(1, buf.head);
    TEST_ASSERT_EQUAL(1, buf.tail);

    // Test popping from a NULL buffer
    TEST_ASSERT_FALSE(ring_buf_pop(NULL, &item));
}

