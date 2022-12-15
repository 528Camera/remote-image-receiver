/**
 * Реализация тестов объекта для чтения и хранения конфигурационных параметров.
 */

#include <boost/log/trivial.hpp>
#include "ConfigurationReader.h"
#include "ConfigurationReaderTests.h"

using namespace receiver;
using namespace std;

void ConfigurationReaderTests::fromFileTest() {
    BOOST_LOG_TRIVIAL(trace) << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__;
    Configuration config;
    // Случай с некорректным файлом.
    string badStr = "bad";
    auto badRes = config.fromFile(badStr);
    // Проверка параметров и результата.
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Неожиданное поведение при загрузке конфигурации", false, badRes);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное значение конфиг-параметра", (unsigned int)0, config.workerPort);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное значение конфиг-параметра", (unsigned int)0, config.backetSize);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное значение конфиг-параметра", (unsigned int)1, config.version);

    // Случай с корректным файлом.
    string goodStr = "tests_data/config.json";
    auto goodRes = config.fromFile(goodStr);
    // Проверка параметров и результата.
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Неожиданное поведение при загрузке конфигурации", true, goodRes);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное значение конфиг-параметра", (unsigned int)8049, config.workerPort);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное значение конфиг-параметра", (unsigned int)20, config.backetSize);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное значение конфиг-параметра", (unsigned int)1, config.version);
}