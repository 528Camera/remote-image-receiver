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
/** Количество записей в хранилище. */
#define STORAGE_SIZE 200

using namespace receiver;
using namespace std;

void AnalyzerTests::setUp() {
    // Инициализация анализатора сообщений.
    pAnalyzer = make_shared<Analyzer>(VERSION);
    MessageStorage::setQuantity(BACKET_SIZE);
    // Запуск анализатора принятых сообщений.
    pAnalyzer->start();
}

void AnalyzerTests::tearDown() {
    // Остановка анализатора принятых сообщений.
    pAnalyzer->stop();
}

void AnalyzerTests::analyzeTest() {
    BOOST_LOG_TRIVIAL(trace) << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__;
    // Формирование тестовых сообщений.
    for (int i = 0; i < STORAGE_SIZE; i++) {
        Message mes;
        mes.set_version(VERSION);
        mes.set_frame_index(STORAGE_SIZE - i - 1);
        mes.set_image("");
        // Сериализация сообщения.
        auto serialized = mes.SerializeAsString();
        // Добавление сообщения в хранилище.
        MessageStorage::addMessage(serialized);
    }
    sleep(1);
    // Проверка проанализированных сообщений.
    CPPUNIT_ASSERT_MESSAGE("Некорректное количество сообщений в хранилище", MessageStorage::getAll().empty());
}