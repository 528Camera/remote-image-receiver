/**
 * Реализация тестов сетевого взаимодействия.
 */

#include <boost/log/trivial.hpp>
#include <future>
#include <vector>
#include <zmq.hpp>
#include "ZmqProxyTests.h"
#include "MessageStorage.h"

/** Строка подключения имитатора. */
#define IMIT_HOST "tcp://127.0.0.1:10001"
/** Размер корзины для теста. */
#define BACKET_SIZE 10

using namespace std;
using namespace zmq;
using namespace receiver;

/** Имитатор отправителя запросов. */
vector<string> imitation() {
    BOOST_LOG_TRIVIAL(trace) << "Запуск имитатора отправителя запросов";
    context_t context(1);
    socket_t sock(context, ZMQ_PUSH);
    sock.connect(IMIT_HOST);
    vector<string> sended;
    // Отправка тестовых сообщений.
    for (int i = 0; i < BACKET_SIZE * 2; i++) {
        // Инциализация сообщения.
        string stream(to_string(i));
        zmq::message_t msg(stream.c_str(), stream.length());
        auto res = sock.send(msg, send_flags::sndmore);
        sended.push_back(stream);
    }
    sock.disconnect(IMIT_HOST);
    sock.close();
    context.close();
    return sended;
}

void ZmqProxyTests::listenerTest() {
    BOOST_LOG_TRIVIAL(trace) << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__;
    string hostName(IMIT_HOST);
    // Инициализация слушателя.
    pZmqListener = make_shared<ZmqProxy>(hostName);
    // Инициализация хранилища.
    MessageStorage::setQuantity((unsigned int)BACKET_SIZE);
    // Запуск прослушивания.
    pZmqListener->startListen();
    // Запуск имитации отправления запросов.
    auto ff = async(imitation);
    // Остановка прослушивания.
    ff.wait();
    auto sendedMes = ff.get();
    pZmqListener->stopListen();
    // Проверка хранилища принятых сообщений.
    auto curMes = MessageStorage::getAll();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное количество сообщений", (int)BACKET_SIZE * 2, (int)sendedMes.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное количество сообщений", (int)BACKET_SIZE * 2, (int)curMes.size());
    for (int i = 0; i < curMes.size(); i++) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное сообщение", sendedMes[i], curMes[i]);
    }
    pZmqListener = nullptr;
}