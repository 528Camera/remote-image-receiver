/**
 * Реализация класса, обеспечивающего сетевое взаимодействие.
 */

#include <boost/log/trivial.hpp>
#include "ZmqProxy.h"
#include "MessageStorage.h"

#define ZMQ_THREADS 1

using namespace std;
using namespace zmq;
using namespace receiver;

ZmqProxy::ZmqProxy(std::string& _url) : url(_url) {
    BOOST_LOG_TRIVIAL(trace) << "Создание объекта для прослушивания ZMQ-сокета...";
    thread = pthread_t();
    isStarted = false;
    stopped = false;
    pContext = make_shared<context_t>(ZMQ_THREADS);
    BOOST_LOG_TRIVIAL(trace) << "Объект для прослушивания ZMQ-сокета успешно создан";
}

void ZmqProxy::startListen() {
    BOOST_LOG_TRIVIAL(trace) << "Запуск прослушивания...";
    if (!isStarted) {
        stopped = false;
        pthread_create(&thread, nullptr, ZmqProxy::threadRoutine, this);
        BOOST_LOG_TRIVIAL(trace) << "Прослушивание запущено";
    } else BOOST_LOG_TRIVIAL(trace) << "Прослушивание уже запущено";
}

void ZmqProxy::stopListen() {
    BOOST_LOG_TRIVIAL(trace) << "Остановка прослушивания...";
    stopped = true;
    pContext = nullptr;
    pthread_join(thread, nullptr);
    thread = pthread_t();
    isStarted = false;
    BOOST_LOG_TRIVIAL(trace) << "Прослушивание остановлено";
}

void* ZmqProxy::threadRoutine(void *arg) {
    // Получение доступа к элементам класса.
    auto _this = (ZmqProxy*)arg;
    // Создание сокета для прослушивания.
    socket_t socket(*_this->pContext, ZMQ_PULL);
    socket.bind(_this->url.c_str());
    // Прослушивание.
    while(!_this->stopped) {
        try {
            // Буфер для принятого сообщения.
            message_t message;
            // Ожидание сообщения.
            auto res = socket.recv(message, recv_flags::none);
            // Буферизация принятого сообщения.
            std::string mes = std::string(static_cast<char*>(message.data()), message.size());
            MessageStorage::addMessage(mes);
        }
        catch(const zmq::error_t& ex)
        {
            // Исключение при вызове stop().
            if(ex.num() != ETERM)
                break;
        }
    }
    socket.close();
    return nullptr;
}