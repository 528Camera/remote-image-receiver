/**
 * Объявление класса, осуществляющего сетевое взаимодействие с воркерами.
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
         /** Контекст ZMQ. */
         zmq::context_t ctx;

         /** Сокет сетевого взаимодействия. */
         zmq::socket_t socket;

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
