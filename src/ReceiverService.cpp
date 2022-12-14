/**
 * Реализация класса сетевого сервиса.
 */

#include <boost/log/trivial.hpp>
#include "ReceiverService.h"

using namespace std;
using namespace receiver;

ReceiverService::ReceiverService(const std::string &configFilename) {
    BOOST_LOG_TRIVIAL(trace) << "Создание сервиса...";
    BOOST_LOG_TRIVIAL(trace) << "Чтение конфигурации...";
    if (!config.fromFile(configFilename)) {
        throw invalid_argument("Не удалось прочитать конфигурационный файл " + configFilename + ".");
    }
    BOOST_LOG_TRIVIAL(trace) << "Конфигурационный файл считан";
    workersAddress = "tcp://" + config.workerHost + ":" + to_string(config.workerPort);
    pZmqProxy = make_shared<ZmqProxy>(workersAddress);
    pAnalyzer = make_shared<Analyzer>(config.version);
    BOOST_LOG_TRIVIAL(trace) << "Сервис создан";
}

void ReceiverService::start() {
    BOOST_LOG_TRIVIAL(trace) << "Запуск сервиса...";

    BOOST_LOG_TRIVIAL(trace) << "Запуск сетевого взаимодействия...";
    pZmqProxy->start();
    BOOST_LOG_TRIVIAL(trace) << "Сетевое взаимодействие запущено";

    BOOST_LOG_TRIVIAL(trace) << "Запуск анализатора принятых сообщений...";
    pAnalyzer->start();
    BOOST_LOG_TRIVIAL(trace) << "Анализатор принятых сообщений запущен";

    started = true;
    BOOST_LOG_TRIVIAL(trace) << "Сервис запущен";
}

void ReceiverService::stop() {
    if (!started) return;
    BOOST_LOG_TRIVIAL(trace) << "Остановка сервиса...";

    BOOST_LOG_TRIVIAL(trace) << "Остановка сетевого взаимодействия...";
    pZmqProxy->stop();
    BOOST_LOG_TRIVIAL(trace) << "Сетевое взаимодействие остановлено";

    BOOST_LOG_TRIVIAL(trace) << "Остановка анализатора принятых сообщений...";
    pAnalyzer->stop();
    BOOST_LOG_TRIVIAL(trace) << "Анализатор принятых сообщений остановлен";

    started = false;
    BOOST_LOG_TRIVIAL(trace) << "Сервис остановлен";
}

bool ReceiverService::isStarted() {
    return started;
}

ReceiverService::~ReceiverService() {
    stop();
    pZmqProxy = nullptr;
    pAnalyzer = nullptr;
}