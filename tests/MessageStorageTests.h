/**
 * Объявление тестов хранилища принятых сообщений.
 */

#ifndef RECEIVER_MESSAGESTORAGETESTS_H
#define RECEIVER_MESSAGESTORAGETESTS_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

/**
 * Тесты хранилища принятых сообщений.
 */
class MessageStorageTests : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(MessageStorageTests);
        CPPUNIT_TEST(setQuantityTest);
        CPPUNIT_TEST(addTest);
        CPPUNIT_TEST(clearTest);
        CPPUNIT_TEST(getMessagesTest);
    CPPUNIT_TEST_SUITE_END();

public:
    /** Тест изменения размера возвращаемого набора сообщений. */
    void setQuantityTest();

    /** Тест добавление нового сообщения. */
    void addTest();

    /** Тест очистки хранилища. */
    void clearTest();

    /** Тест получения набора сообщений. */
    void getMessagesTest();
};

CPPUNIT_TEST_SUITE_REGISTRATION(MessageStorageTests);

#endif //RECEIVER_MESSAGESTORAGETESTS_H
