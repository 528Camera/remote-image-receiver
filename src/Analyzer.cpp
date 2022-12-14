/**
 * Реализация анализатора принятых сообщений.
 */

#include "Analyzer.h"
#include "MessageStorage.h"

using namespace receiver;
using namespace std;

Analyzer::Analyzer(std::int32_t version) : protoVersion(version) {
    pFrameStreamer = make_shared<FrameStreamer>();
    thread = pthread_t();
    isStarted = false;
    stopped = false;
}

Analyzer::~Analyzer() {
    stop();
    pFrameStreamer = nullptr;
}

bool Analyzer::compareById(const Message &a, const Message &b) {
    return a.frame_index() < b.frame_index();
}

std::vector<Message> Analyzer::deserialize() {
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
    return deserializedMessages;
}

std::vector<Message> Analyzer::analyze() {
    // Десериализация набора принятых сообщений.
    auto messages = deserialize();
    // Сортировка сообщений.
    sort(messages.begin(), messages.end(), compareById);
    return messages;
}

void Analyzer::start() {
    if (!isStarted) {
        stopped = false;
        isStarted = true;
        thread = pthread_t();
        pthread_create(&thread, nullptr, Analyzer::threadRoutine, this);
    }
}

void Analyzer::stop() {
    if (!isStarted) return;
    stopped = true;
    isStarted = false;
    pFrameStreamer = nullptr;
    pthread_join(thread, nullptr);
}

void* Analyzer::threadRoutine(void *arg) {
    // Получение доступа к элементам класса.
    auto _this = (Analyzer*)arg;
    // Анализ принятых сообщений.
    while(!_this->stopped) {
        // Анализ последних принятых сообщений.
        auto anMes = _this->analyze();
        // Показ последних принятых сообщений.
        _this->pFrameStreamer->showImages(anMes);
    }
    return nullptr;
}