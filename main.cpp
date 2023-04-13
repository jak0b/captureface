#include <iostream>
#include <chrono>
#include <thread>

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

auto detectFace(cv::CascadeClassifier &cascade, cv::Mat &frame) {
  cv::Mat prepFrame;
  std::vector<cv::Rect> faces;

  cv::cvtColor(frame, prepFrame, cv::COLOR_BGR2GRAY);
  cv::equalizeHist(prepFrame, prepFrame);
  cascade.detectMultiScale(prepFrame, faces);

  return faces.size();
}

int main(int argc, const char** argv) {
    for (auto i = 0; i < argc; i++)
        std::cout << argv[i] << std::endl;

    std::chrono::duration<int, std::milli> ten_sec(10000);
    std::chrono::duration<int, std::milli> one_sec(1000);
    cv::CascadeClassifier cascade;

    /* TODO */
    /* find a way to embed the xml file inside the binary */
    auto load_result = cascade.load("./files/haarcascade_frontalface_default.xml");
    if(!load_result) {
      std::cerr << "Error loading face cascade" << std::endl;
        return -1;
    };

    auto camera_device = 5;
    // TODO
    // write a fucntion that traverses through available cameras and selects the one that is
    // applicable to the current hardware context e.g one that doesn't caputre a black frame

    cv::Mat frame;

    for (;;) {
      cv::VideoCapture capture;
      capture.open(camera_device);
      if (!capture.isOpened()) {
        std::cerr << "Error opening video capture" << std::endl;
        return 2;
      }

      std::this_thread::sleep_for(one_sec);
      capture.read(frame);
      if(frame.empty()) {
        std::cerr << "No frame captured" << std::endl;
        return 3;
      }

      auto faces = detectFace(cascade, frame);

      auto faces_message = faces == 1 ? "face was deteced" : "faces were deteced";

      std::cout << faces << " " << faces_message << std::endl;

      capture.release();
      std::this_thread::sleep_for(ten_sec);
    }

    return 0;
}
