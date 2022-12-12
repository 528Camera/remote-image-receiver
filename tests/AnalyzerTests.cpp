/**
 * Реализация тестов анализатора принятых сообщений.
 */

#include <boost/log/trivial.hpp>
#include <proto/message.pb.h>
#include "AnalyzerTests.h"
#include "MessageStorage.h"

/** Тестовый номер версии. */
#define VERSION 1
/** Тестовый размер обрабатываемой корзины. */
#define BACKET_SIZE 20

using namespace receiver;
using namespace std;

void AnalyzerTests::setUp() {
    // Инициализация анализатора сообщений.
    pAnalyzer = make_shared<Analyzer>(VERSION);
    MessageStorage::setQuantity(BACKET_SIZE);
}

void AnalyzerTests::tearDown() {
    pAnalyzer = nullptr;
}

void AnalyzerTests::analyzeTest() {
    BOOST_LOG_TRIVIAL(trace) << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__;
    // Формирование тестовых сообщений.
    for (int i = 0; i < BACKET_SIZE * 2; i++) {
        Message mes;
        mes.set_version(VERSION);
        mes.set_frame_id(BACKET_SIZE * 2 - i - 1);
        mes.set_timestamp(0);
        mes.set_image_data("");
        // Сериализация сообщения.
        auto serialized = mes.SerializeAsString();
        // Добавление сообщения в хранилище.
        MessageStorage::addMessage(serialized);
    }
    // Анализ принятых сообщений.
    auto analyzedMessages = pAnalyzer->analyze();
    // Проверка проанализированных сообщений.
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное количество сообщений", (int)BACKET_SIZE, (int)analyzedMessages.size());
    for (int i = 0; i < analyzedMessages.size(); i++) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное количество сообщений", (int)BACKET_SIZE + i, (int)analyzedMessages[i].frame_id());
    }
}