/**
 * Объявление тестов объекта для показа/хранения принятых изображений.
 */

#ifndef RECEIVER_FRAMESTREAMERTESTS_H
#define RECEIVER_FRAMESTREAMERTESTS_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "FrameStreamer.h"

/**
 * Тесты объекта для показа/хранения принятых изображений.
 */
class FrameStreamerTests : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(FrameStreamerTests);
        CPPUNIT_TEST(showTest);
    CPPUNIT_TEST_SUITE_END();

public:
    /** Инициализация данных теста. */
    void setUp() override;

    /** Освобождение ресурсов теста. */
    void tearDown() override;

    /** Тест изменения размера возвращаемого набора сообщений. */
    void showTest();

private:
    /** Обработчик кадров. */
    std::shared_ptr<receiver::FrameStreamer> pFrameStreamer;
};

#endif //RECEIVER_FRAMESTREAMERTESTS_H
