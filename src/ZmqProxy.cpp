/**
 * Реализация класса, обеспечивающего сетевое взаимодействие.
 */

#include <boost/log/trivial.hpp>
#include <chrono>
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
    // Время прихода предыдущего пакета, мс.
    auto prevPacketTime = chrono::system_clock::now();
    // Среднее время прихода сообщения, мс.
    auto avgRecvTime = (long)0;
    // Флаг первого принятого пакета.
    auto isFirstPacket = true;
    // Прослушивание.
    while(!_this->stopped) {
        try {
            // Буфер для принятого сообщения.
            message_t message;
            // Ожидание сообщения.
            auto res = socket.recv(message, recv_flags::none);
            // Время получения пакета.
            auto nowPacketTime = chrono::system_clock::now();
            // Если принят не первый пакет - расчёт производительности.
            if (!isFirstPacket) {
                auto diffMs = chrono::duration_cast<std::chrono::milliseconds>(
                        nowPacketTime - prevPacketTime).count();
                avgRecvTime += diffMs;
            }
            // Сохранение времени получения пакета.
            prevPacketTime = nowPacketTime;
            // Буферизация принятого сообщения.
            string mes = string(static_cast<char*>(message.data()), message.size());
            MessageStorage::addMessage(mes);
            // Вывод времени, усредненный по размеру корзины.
            auto quantity = MessageStorage::getQuantity();
            if (MessageStorage::getAll().size() % quantity == 0) {
                BOOST_LOG_TRIVIAL(trace) << "Среднее время прихода кадра: " << avgRecvTime / quantity << " мс";
                avgRecvTime = (long)0;
            }
            // Изменение флага получения первого пакета.
            if (isFirstPacket) isFirstPacket = false;
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