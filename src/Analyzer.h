/**
 * Объявление анализатора принятых сообщений.
 */

#ifndef ZMQ_RECEIVER_ANALYZER_H
#define ZMQ_RECEIVER_ANALYZER_H

#include <vector>
#include <proto/message.pb.h>

namespace receiver {
    /**
     * Анализатор принятых сообщений.
     */
    class Analyzer {
        /** Ожидаемая версия протокола. */
        std::int32_t protoVersion;

        /** Сравнить структуры. */
        static bool compareById(const Message& a, const Message& b);

        /**
         * Десериализовать набор принятых сообщений.
         * @return десериализованный набор сообщений.
         */
        std::vector<Message> deserialize();

    public:
        /**
         * Конструктор.
         * @param version номер версии протокола.
         */
        Analyzer(std::int32_t version);

        /**
         * Выполнить анализ и сортировку набора принятых сообщений.
         * @return проанализированные и отсортированные сообщения.
         */
        std::vector<Message> analyze();
    };
}

#endif //ZMQ_RECEIVER_ANALYZER_H
