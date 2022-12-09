/**
 * Объявление тестов объекта для чтения и хранения конфигурационных параметров.
 */

#include "ConfigurationReader.h"
#include "ConfigurationReaderTests.h"

using namespace receiver;
using namespace std;

void ConfigurationReaderTests::fromFileTest()
{
    Configuration config;
    // Случай с некорректным файлом.
    string badStr = "bad";
    auto badRes = config.fromFile(badStr);
    // Проверка параметров и результата.
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Неожиданное поведение при загрузке конфигурации", false, badRes);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное значение конфиг-параметра", (unsigned int)0, config.workerPort);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное значение конфиг-параметра", (unsigned int)0, config.backetSize);

    // Случай с корректным файлом.
    string goodStr = "tests_data/config.json";
    auto goodRes = config.fromFile(goodStr);
    // Проверка параметров и результата.
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Неожиданное поведение при загрузке конфигурации", true, goodRes);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное значение конфиг-параметра", (unsigned int)8049, config.workerPort);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное значение конфиг-параметра", (unsigned int)5, config.backetSize);
}