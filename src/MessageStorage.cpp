/**
 * Реализация хранилища принятых сообщений.
 */

#include "MessageStorage.h"

using namespace receiver;
using namespace std;

vector<string> MessageStorage::acMessages;
mutex MessageStorage::mutex;
unsigned int MessageStorage::backetSize;

void MessageStorage::setQuantity(unsigned int count) {
    std::lock_guard<std::mutex> lock(mutex);
    backetSize = count;
}

unsigned int MessageStorage::getQuantity() {
    std::lock_guard<std::mutex> lock(mutex);
    return backetSize;
}

void MessageStorage::addMessage(const char *message) {
    string mes(message);
    addMessage(mes);
}

void MessageStorage::addMessage(string &message) {
    std::lock_guard<std::mutex> lock(mutex);
    acMessages.push_back(message);
}

vector<string> MessageStorage::getMessages() {
    std::lock_guard<std::mutex> lock(mutex);
    // Буфер для результата.
    vector<string> result;
    // Проверка нужного количества записей в хранилище.
    if (acMessages.size() < backetSize) return result;

    // Копирование сообщений.
    for (int i = 0; i < backetSize; i++) {
        result.push_back(acMessages[i]);
    }
    // Удаление обработанных записей.
    vector<string> remaining(acMessages.begin()+backetSize, acMessages.end());
    acMessages = remaining;
    return result;
}

std::vector<std::string> MessageStorage::getAll() {
    std::lock_guard<std::mutex> lock(mutex);
    return acMessages;
}

void MessageStorage::clear() {
    std::lock_guard<std::mutex> lock(mutex);
    acMessages.clear();
}