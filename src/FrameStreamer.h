/**
 * Объявление логики сохранения обработанных кадров.
 */

#ifndef ZMQ_RECEIVER_FRAMESAVER_H
#define ZMQ_RECEIVER_FRAMESAVER_H

#include <vector>
#include <proto/message.pb.h>

namespace receiver {
    /**
     * Обработчик, для сохранения проанализированных сообщений.
     */
    class FrameStreamer {
    public:
        /**
         * Сохранение обработанных изображений.
         * @param mes обработанные изображения.
         */
        void showImages(std::vector<Message>& mes);

        /**
         * Деструктор.
         */
        ~FrameStreamer();
    };
}

#endif //ZMQ_RECEIVER_FRAMESAVER_H
