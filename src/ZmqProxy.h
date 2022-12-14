/**
 * Объявление класса, обеспечивающего сетевое взаимодействие.
 */

#ifndef RECEIVER_ZMQPROXY_H
#define RECEIVER_ZMQPROXY_H

#include <zmq.hpp>
#include <zmq_addon.hpp>

namespace receiver {
    /**
     * Объект сетевого взаимодействия с помощью ZMQ.
     */
    class ZmqProxy {
        /** Адрес для прослушивания. */
        std::string url;

        /** Поток для исполнения. */
        pthread_t thread;

        /** Флаг запуска прослушивания. */
        bool isStarted;

        /** Флаг остановки. */
        bool stopped;

        /** Контекст ZMQ. */
        std::shared_ptr<zmq::context_t> pContext;

        /** Функция потока. */
        static void* threadRoutine(void*);

    public:
        /**
         * Конструктор.
         */
        ZmqProxy(std::string& _url);

        /**
         * Запустить прослушивание PULL сокета.
         */
        void start();

        /**
         * Остановить прослушивание PULL сокета.
         */
        void stop();
    };
}

#endif //RECEIVER_ZMQPROXY_H
