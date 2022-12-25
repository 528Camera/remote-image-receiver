/**
 * Реализация тестов объекта для показа/хранения принятых изображений.
 */

#include <vector>
#include <boost/log/trivial.hpp>
#include <opencv2/opencv.hpp>
#include "FrameStreamerTests.h"

/** Путь до видеофайла. */
#define VIDEO_PATH "tests_data/test_video.mp4"
/** Тестовый номер версии. */
#define VERSION 1
/** Количество кадров для теста. */
#define FRAME_COUNT 20

using namespace std;
using namespace receiver;
using namespace cv;

/** Конвертировать изображение к байтовой строке. */
string matToVectorUint(Mat& img) {
    // Буфер для результата.
    vector<uchar> buf;
    imencode(".jpg",img,buf);
    std::string str(buf.begin(), buf.end());
    return str;
}

void FrameStreamerTests::setUp() {
    pFrameStreamer = make_shared<FrameStreamer>();
}

void FrameStreamerTests::tearDown() {
    pFrameStreamer = nullptr;
}

void FrameStreamerTests::showTest() {
    BOOST_LOG_TRIVIAL(trace) << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__;
    // Объект для чтения тестового видео.
    VideoCapture capture(VIDEO_PATH);
    // Проверка открытия видеопотока.
    if(!capture.isOpened())
        CPPUNIT_ASSERT_MESSAGE("Ошибка при открытии видеофайла", false);

    // Набор кадров.
    vector<Message> images;
    auto counter = 1;
    // Кадр видео.
    Mat frame;
    // Чтение видео.
    for(;;) {
        capture >> frame;

        if (frame.empty() || counter > FRAME_COUNT)
            break;

        // Формирование сообщения.
        Message mes;
        mes.set_version(VERSION);
        mes.set_image(matToVectorUint(frame));
        mes.set_frame_index(counter);
        // Добавление сообщения к общему набору.
        images.push_back(mes);
        counter++;
    }
    // Передача набора изображений
    pFrameStreamer->showImages(images);
}