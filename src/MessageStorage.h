/**
 * Объявление хранилища принятых сообщений.
 */

#ifndef ZMQ_RECEIVER_MESSAGESTORAGE_H
#define ZMQ_RECEIVER_MESSAGESTORAGE_H

#include <vector>
#include <string>
#include <mutex>

namespace receiver {
    /**
     * Хранилище принятых сообщений по ZMQ.
     */
    class MessageStorage {
        /** Хранилище принятых сообщений. */
        static std::vector<std::string> acMessages;

        /** Мьютекс. */
        static std::mutex mutex;

        /** Размер возвращаемого набора сообщений. */
        static unsigned int backetSize;

    public:
        /**
         * Установить размер возвращаемого набора сообщений.
         * @param count количество сообщений.
         */
        static void setQuantity(unsigned int count);

        /**
         * Получить текущий размер возвращаемого набора сообщений.
         */
        static unsigned int getQuantity();

        /**
         * Добавить сообщение в хранилище.
         * @param message принятое сообщение.
         */
        static void addMessage(std::string& message);

        /**
         * Добавить сообщение в хранилище.
         * @param message принятое сообщение.
         */
        static void addMessage(const char* message);

        /**
         * Получить набор сообщений из хранилища (с удалением).
         * @return набор сообщений.
         */
        static std::vector<std::string> getMessages();

        /**
         * Получить все принятые сообщения из хранилища.
         */
        static std::vector<std::string> getAll();

        /**
         * Очистить хранилище.
         */
        static void clear();
    };
}

#endif //ZMQ_RECEIVER_MESSAGESTORAGE_H
