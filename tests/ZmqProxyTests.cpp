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
#define IMIT_HOST "tcp://*:10001"
/** Строка для сетевого взаимодействия с имитатором. */
#define ZMQ_HOST "tcp://127.0.0.1:10001"
/** Размер корзины для теста. */
#define BACKET_SIZE 20

using namespace std;
using namespace zmq;
using namespace receiver;

/** Имитатор отправителя запросов. */
vector<string> imitation() {
    BOOST_LOG_TRIVIAL(trace) << "Запуск имитатора отправителя запросов";
    context_t context(1);
    socket_t sock(context, socket_type::push);
    sock.bind(IMIT_HOST);
    vector<string> sended;
    // Отправка тестовых сообщений.
    for (int i = 0; i < BACKET_SIZE; i++) {
        // Инциализация сообщения.
        string stream(to_string(i));
        zmq::message_t msg(stream.c_str(), stream.length());
        auto res = sock.send(msg, send_flags::none);
        sended.push_back(stream);
    }
    sock.close();
    context.close();
    return sended;
}

void ZmqProxyTests::setUp() {
    string hostName(ZMQ_HOST);
    // Инициализация слушателя.
    pZmqListener = make_shared<ZmqProxy>(hostName);
    // Запуск прослушивания.
    pZmqListener->start();
}

void ZmqProxyTests::tearDown() {
    // Остановка прослушивания.
    pZmqListener->stop();
    pZmqListener = nullptr;
}

void ZmqProxyTests::listenerTest() {
    BOOST_LOG_TRIVIAL(trace) << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__;
    // Инициализация хранилища.
    MessageStorage::setQuantity((unsigned int)BACKET_SIZE);
    MessageStorage::clear();
    // Запуск имитации отправления запросов.
    auto ff = async(imitation);
    auto sendedMes = ff.get();
    // Проверка хранилища принятых сообщений.
    auto curMes = MessageStorage::getAll();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное количество сообщений", (int)BACKET_SIZE, (int)sendedMes.size());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное количество сообщений", (int)BACKET_SIZE, (int)curMes.size());
    for (int i = 0; i < curMes.size(); i++) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Некорректное сообщение", sendedMes[i], curMes[i]);
    }
}