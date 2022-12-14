/**
 * Реализация логики сохранения обработанных кадров.
 */

#include <opencv2/opencv.hpp>
#include "FrameStreamer.h"

/** Название окна. */
#define WINNAME "Received image"

using namespace std;
using namespace receiver;
using namespace cv;

void FrameStreamer::showImages(std::vector<Message> &mes) {
    // Обработка изображений.
    for (auto& m : mes) {
        // Вектор байтов изображения.
        auto imgStr = m.image();
        vector<uint8_t> imgBytes(imgStr.begin(), imgStr.end());
        // Получение изображения.
        Mat imgData(imgBytes, true);
        // Декодирование изображения.
        try {
            Mat img(imdecode(imgData, 1));
            // Отображение изображений.
            namedWindow(WINNAME);
            moveWindow(WINNAME, 0, 0);
            imshow(WINNAME, img);
            waitKey(1);
        } catch(const exception& ex) {}
    }
}

FrameStreamer::~FrameStreamer() {
    destroyAllWindows();
}