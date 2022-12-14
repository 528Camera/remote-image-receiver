/**
 * Объявление объекта для чтения и хранения конфигурационных параметров.
 */

#ifndef ZMQ_RECEIVER_CONFIGURATIONREADER_H
#define ZMQ_RECEIVER_CONFIGURATIONREADER_H

#include <string>

namespace receiver {
    /**
     * Хранилище конфигурационных параметров.
     */
    struct Configuration {
        /** Порт для взаимодействия с обработчиками кадров. */
        unsigned int workerPort = 0;

        /** Адрес для взаимодействия с обработчиком кадров. */
        std::string workerHost = "127.0.0.1";

        /** Размер партии обрабатываемых анализатором изображений. */
        unsigned int backetSize = 0;

        /** Номер версии. */
        unsigned int version = 1;

        /**
         * Конструктор по умолчанию.
         */
         explicit Configuration() = default;

         /**
          * Загрузить конфигурацию из файла.
          * @param filename имя файла.
          * @return успешность загрузки конфигурации.
          */
         bool fromFile(const std::string& filename);
    };
}

#endif //ZMQ_RECEIVER_CONFIGURATIONREADER_H
