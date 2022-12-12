/**
 * Реализация хранилища принятых сообщений.
 */

#include "MessageStorage.h"

using namespace receiver;
using namespace std;

vector<string> MessageStorage::acMessages;
unsigned int MessageStorage::backetSize;

void MessageStorage::setQuantity(unsigned int count) {
    backetSize = count;
}

unsigned int MessageStorage::getQuantity() {
    return backetSize;
}

void MessageStorage::addMessage(const char *message) {
    string mes(message);
    addMessage(mes);
}

void MessageStorage::addMessage(string &message) {
    acMessages.push_back(message);
}

vector<string> MessageStorage::getMessages() {
    // Буфер для результата.
    vector<string> result;
    // Получение количества записей.
    auto size = backetSize;
    if (acMessages.size() < backetSize) size = acMessages.size();
    // Копирование сообщений.
    for (int i = 0; i < size; i++) {
        result.push_back(acMessages[i]);
    }
    // Удаление обработанных записей.
    vector<string> remaining(acMessages.begin(), acMessages.begin()+backetSize);
    acMessages = remaining;
    return result;
}

std::vector<std::string> MessageStorage::getAll() {
    return acMessages;
}

void MessageStorage::clear() {
    acMessages.clear();
}