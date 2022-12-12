/**
 * Реализация анализатора принятых сообщений.
 */

#include <boost/log/trivial.hpp>
#include "Analyzer.h"
#include "MessageStorage.h"

using namespace receiver;
using namespace std;

Analyzer::Analyzer(std::int32_t version) : protoVersion(version) {}

bool Analyzer::compareById(const Message &a, const Message &b) {
    return a.frame_id() < b.frame_id();
}

std::vector<Message> Analyzer::deserialize() {
    BOOST_LOG_TRIVIAL(trace) << "Запущен анализ принятых сообщений";
    // Получение принятых сообщений.
    auto acMessages = MessageStorage::getMessages();
    // Буфер для хранения десериализованных структур.
    vector<Message> deserializedMessages;
    for (auto& mes : acMessages) {
        // Десериализация сообщения.
        Message message;
        // Если сообщение не удалось обработать - пропуск.
        if (!message.ParseFromString(mes)) continue;
        // Проверка версии протокола.
        if (message.version() != protoVersion) continue;
        // Добавление десериализованного сообщения в буфер.
        deserializedMessages.push_back(message);
    }
    BOOST_LOG_TRIVIAL(trace) << "Анализ принятых сообщений завершен";
    return deserializedMessages;
}

std::vector<Message> Analyzer::analyze() {
    // Десериализация набора принятых сообщений.
    auto messages = deserialize();
    // Сортировка сообщений.
    sort(messages.begin(), messages.end(), compareById);
    return messages;
}