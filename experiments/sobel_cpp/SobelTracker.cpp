#include "SobelTracker.h"

#include <QApplication>
#include <QIntValidator>
#include <QPushButton>
#include <QPainter>

#include <biotracker/TrackingAlgorithm.h>
#include <biotracker/Registry.h>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

cv::Mat ONE = cv::Mat::ones(1,1,CV_8UC1);

extern "C" {
    void registerTracker() {
        BioTracker::Core::Registry::getInstance().registerTrackerType<SobelTracker>("SobelTracker");
    }
}

SobelTracker::SobelTracker(Settings &settings)
    : TrackingAlgorithm(settings)
    , m_mat(ONE)
     {
}

void SobelTracker::track(ulong, const cv::Mat &imgOriginal) {

    cv::Mat gray;
    cv::Mat grad_x, grad_y;
    cv::cvtColor(imgOriginal, gray, CV_BGR2GRAY);
    cv::Sobel(gray, grad_x, CV_16S, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
    cv::Sobel(gray, grad_y, CV_16S, 0, 1, 3, 1, 0, cv::BORDER_DEFAULT);

    m_mat = grad_x;
}

void SobelTracker::paint(ProxyMat &m, const TrackingAlgorithm::View &view)
{
    m.setMat(m_mat);
}


void SobelTracker::paintOverlay(QPainter *painter, const View &view) {
}
