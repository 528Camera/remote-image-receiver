/**
 * Реализация тестов хранилища принятых сообщений.
 */

#include <boost/log/trivial.hpp>
#include "MessageStorage.h"
#include "MessageStorageTests.h"

/** Количество возвращаемых сообщений для теста. */
#define COUNT 20

using namespace receiver;
using namespace std;

void MessageStorageTests::setQuantityTest() {
    BOOST_LOG_TRIVIAL(trace) << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__;
    MessageStorage::setQuantity(COUNT);
    // Проверка установленного параметра.
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное значение параметра", (unsigned int)COUNT, (unsigned int)MessageStorage::getQuantity());
}

void MessageStorageTests::addTest() {
    BOOST_LOG_TRIVIAL(trace) << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__;
    // Проверка хранилища на пустоту.
    MessageStorage::clear();
    CPPUNIT_ASSERT_MESSAGE("Некорректное количество сообщений в хранилище", MessageStorage::getAll().empty());
    // Добавление тестовых записей в хранилище.
    const char* mes1("test-1");
    string mes2("test-2");
    MessageStorage::addMessage(mes1);
    MessageStorage::addMessage(mes2);
    // Проверка размера хранилища.
    auto curMessages = MessageStorage::getAll();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное количество сообщений в хранилище", (int)2, (int)curMessages.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное сообщениe", string(mes1), curMessages.front());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное сообщениe", mes2, curMessages.back());
}

void MessageStorageTests::clearTest() {
    BOOST_LOG_TRIVIAL(trace) << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__;
    // Проверка пустоты хранилища.
    CPPUNIT_ASSERT_MESSAGE("Некорректное количество сообщений в хранилище", !MessageStorage::getAll().empty());
    // Очистка хранилища.
    MessageStorage::clear();
    CPPUNIT_ASSERT_MESSAGE("Некорректное количество сообщений в хранилище", MessageStorage::getAll().empty());
}

void MessageStorageTests::getMessagesTest() {
    BOOST_LOG_TRIVIAL(trace) << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__;
    // Очистка хранилища перед тестом.
    MessageStorage::clear();
    // Добавление тестовых записей в хранилище.
    for (int i = 0; i < COUNT * 2; i++) {
        string value(to_string(i));
        MessageStorage::addMessage(value);
    }
    // Проверка текущего размера корзины.
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректный размер корзины", (int)COUNT, (int)MessageStorage::getQuantity());
    // Получение корзины.
    auto curMessages = MessageStorage::getMessages();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное количество сообщений", (int)COUNT, (int)curMessages.size());
    for (int i = 0; i < curMessages.size(); i++) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное сообщение", to_string(i), curMessages[i]);
    }
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное количество сообщений в хранилище", (int)COUNT, (int)MessageStorage::getAll().size());
}