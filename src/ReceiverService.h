/**
 * Объявление класса сетевого сервиса.
 */

#ifndef ZMQ_RECEIVER_ZMQPROXY_H
#define ZMQ_RECEIVER_ZMQPROXY_H

#include <zmq.hpp>
#include <zmq_addon.hpp>

namespace receiver {
    /**
     * Сервис обработчика кадров, полученных через сетевое взаимодействие.
     */
     class ReceiverService {
         // TODO: Умные указатели.

     public:
         /**
          * Конструктор.
          */
         ReceiverService();

         /**
          * Деструктор.
          */
         ~ReceiverService();

         /**
          * Запуск сервиса.
          */
         void start();

         /**
          * Остановка сервиса.
          */
         void stop();
     };
}

#endif //ZMQ_RECEIVER_ZMQPROXY_H
