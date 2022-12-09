/**
 * Объявление тестов объекта для чтения и хранения конфигурационных параметров.
 */

#ifndef ZMQ_RECEIVER_CONFIGURATIONREADERTESTS_H
#define ZMQ_RECEIVER_CONFIGURATIONREADERTESTS_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

/**
 * Тесты чтения и хранения конфигурационных параметров.
 */
class ConfigurationReaderTests : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ConfigurationReaderTests);
        CPPUNIT_TEST(fromFileTest);
    CPPUNIT_TEST_SUITE_END();

public:
    /** Тест чтения конфигурационного файла. */
    void fromFileTest();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ConfigurationReaderTests);

#endif //ZMQ_RECEIVER_CONFIGURATIONREADERTESTS_H
