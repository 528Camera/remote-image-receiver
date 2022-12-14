/**
 * Объявление анализатора принятых сообщений.
 */

#ifndef ZMQ_RECEIVER_ANALYZER_H
#define ZMQ_RECEIVER_ANALYZER_H

#include <vector>
#include <proto/message.pb.h>
#include "FrameStreamer.h"

namespace receiver {
    /**
     * Анализатор принятых сообщений.
     */
    class Analyzer {
        /** Ожидаемая версия протокола. */
        std::int32_t protoVersion;

        /** Поток для исполнения. */
        pthread_t thread;

        /** Флаг остановки. */
        bool stopped;

        /** Флаг запуска прослушивания. */
        bool isStarted;

        /** Объект для отображения проанализированных сообщений. */
        std::shared_ptr<FrameStreamer> pFrameStreamer;

        /** Сравнить структуры. */
        static bool compareById(const Message& a, const Message& b);

        /**
         * Десериализовать набор принятых сообщений.
         * @return десериализованный набор сообщений.
         */
        std::vector<Message> deserialize();

        /**
         * Выполнить анализ и сортировку набора принятых сообщений.
         * @return проанализированные и отсортированные сообщения.
         */
        std::vector<Message> analyze();

        /** Функция потока. */
        static void* threadRoutine(void*);

    public:
        /**
         * Конструктор.
         * @param version номер версии протокола.
         */
        Analyzer(std::int32_t version);

        /**
         * Деструктор.
         */
        ~Analyzer();

        /**
         * Запуск анализатор принятых сообщений.
         */
        void start();

        /**
         * Остновка анализатора принятых сообщений.
         */
        void stop();
    };
}

#endif //ZMQ_RECEIVER_ANALYZER_H
