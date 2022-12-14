/**
 * Объявление тестов сетевого взаимодействия.
 */

#ifndef RECEIVER_ZMQPROXYTESTS_H
#define RECEIVER_ZMQPROXYTESTS_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "ZmqProxy.h"

/**
 * Тесты сетевого взаимодействия.
 */
class ZmqProxyTests : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ZmqProxyTests);
        CPPUNIT_TEST(listenerTest);
    CPPUNIT_TEST_SUITE_END();

public:
    /** Инициализация объектов теста. */
    void setUp() override;

    /** Освобождение ресурсов теста. */
    void tearDown() override;

    /** Тест сетевого взаимодействия. */
    void listenerTest();

private:
    /** Объект для сетевого взаимодействия. */
    std::shared_ptr<receiver::ZmqProxy> pZmqListener;
};

#endif //RECEIVER_ZMQPROXYTESTS_H
