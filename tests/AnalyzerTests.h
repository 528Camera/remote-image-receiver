/**
 * Объявление тестов анализатора принятых сообщений.
 */

#ifndef RECEIVER_ANALYZERTESTS_H
#define RECEIVER_ANALYZERTESTS_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Analyzer.h"

/**
 * Тесты анализатора принятых сообщений.
 */
class AnalyzerTests : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(AnalyzerTests);
        CPPUNIT_TEST(analyzeTest);
    CPPUNIT_TEST_SUITE_END();

public:
    /** Инициализация объектов теста. */
    void setUp() override;

    /** Освобождение ресурсов теста. */
    void tearDown() override;

    /** Тест анализа принятых сообщений. */
    void analyzeTest();

private:
    /** Анализатор принятых сообщений. */
    std::shared_ptr<receiver::Analyzer> pAnalyzer;
};

#endif //RECEIVER_ANALYZERTESTS_H
