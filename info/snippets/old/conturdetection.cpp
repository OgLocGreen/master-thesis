#include <opencv2/opencv.hpp>

int main()
{
    // Bild laden
    cv::Mat image = cv::imread("bild.jpg", cv::IMREAD_COLOR);
    
    if (image.empty())
    {
        std::cout << "Konnte Bild nicht laden!" << std::endl;
        return -1;
    }

    // Bild in Graustufen konvertieren
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    // Bildschwellenwertung // Gelb
    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);
    cv::Scalar lower_yellow(0, 100, 100);
    cv::Scalar upper_yellow(30, 255, 255);
    cv::inRange(hsv, lower_yellow, upper_yellow, gray);
    cv::threshold(gray, gray, 200, 255, cv::THRESH_BINARY);

    //weiß
    //cv::threshold(gray, gray, 200, 255, cv::THRESH_BINARY);


    // Konturerkennung
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(gray, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // Leeres Bild für die Konturen erstellen
    cv::Mat contoursImage = cv::Mat::zeros(image.size(), CV_8UC1);

    // Konturen im Konturenbild zeichnen
    for (size_t i = 0; i < contours.size(); i++)
    {
        cv::drawContours(contoursImage, contours, static_cast<int>(i), cv::Scalar(255), cv::FILLED);
    }

    // Ergebnisbild anzeigen
    cv::imshow("Konturerkennung", contoursImage);
    cv::waitKey(0);

    return 0;
}
