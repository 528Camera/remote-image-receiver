/**
 * Объявление класса сетевого сервиса.
 */

#ifndef ZMQ_RECEIVER_ZMQPROXY_H
#define ZMQ_RECEIVER_ZMQPROXY_H

#include "ConfigurationReader.h"
#include "ZmqProxy.h"
#include "Analyzer.h"
#include "FrameStreamer.h"

namespace receiver {
    /**
     * Сервис обработчика кадров, полученных через сетевое взаимодействие.
     */
     class ReceiverService {
         /** Флаг запуска сервиса. */
         bool started;

         /** Конфигурация, загруженная из файла. */
         Configuration config;

         /** Адрес для подключения с воркерами. */
         std::string workersAddress;

         /** Объект для сетевого взаимодействия. */
         std::shared_ptr<receiver::ZmqProxy> pZmqProxy;

         /** Анализатор принятых сообщений. */
         std::shared_ptr<receiver::Analyzer> pAnalyzer;

     public:
         /**
          * Конструктор.
          * @param configFilename имя файла конфигурации.
          */
         ReceiverService(const std::string& configFilename);

         /**
         * Запуск сервиса.
         */
         void start();

         /**
          * Остановка сервиса.
          */
         void stop();

         /**
          * Проверка постояния сервиса.
          * @return запущен или нет.
          */
         bool isStarted();

         /**
          * Деструктор.
          */
         ~ReceiverService();
     };
}

#endif //ZMQ_RECEIVER_ZMQPROXY_H
