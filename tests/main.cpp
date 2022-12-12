/**
 * Точка входа для модульных тестов.
 */

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include "ConfigurationReaderTests.h"
#include "MessageStorageTests.h"
#include "ZmqProxyTests.h"
#include "AnalyzerTests.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ConfigurationReaderTests);
CPPUNIT_TEST_SUITE_REGISTRATION(MessageStorageTests);
CPPUNIT_TEST_SUITE_REGISTRATION(ZmqProxyTests);
CPPUNIT_TEST_SUITE_REGISTRATION(AnalyzerTests);

int main()
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    bool wasSuccessful = runner.run();
    return !wasSuccessful;
}