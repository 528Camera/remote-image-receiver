/**
 * Реализация класса, обеспечивающего сетевое взаимодействие.
 */

#include "ZmqProxy.h"
#include "MessageStorage.h"

#define ZMQ_THREADS 1

using namespace std;
using namespace zmq;
using namespace receiver;

ZmqProxy::ZmqProxy(std::string& _url) : url(_url) {
    thread = pthread_t();
    isStarted = false;
    stopped = false;
    pContext = make_shared<context_t>(ZMQ_THREADS);
}

void ZmqProxy::start() {
    if (!isStarted) {
        stopped = false;
        isStarted = true;
        thread = pthread_t();
        pthread_create(&thread, nullptr, ZmqProxy::threadRoutine, this);
    }
}

void ZmqProxy::stop() {
    stopped = true;
    isStarted = false;
    pContext = nullptr;
    pthread_join(thread, nullptr);
}

void* ZmqProxy::threadRoutine(void *arg) {
    // Получение доступа к элементам класса.
    auto _this = (ZmqProxy*)arg;
    // Создание сокета для прослушивания.
    socket_t socket(*_this->pContext, socket_type::pull);
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