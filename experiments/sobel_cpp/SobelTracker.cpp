#include "SobelTracker.h"

#include <QApplication>
#include <QIntValidator>
#include <QPushButton>
#include <QPainter>

#include <biotracker/TrackingAlgorithm.h>
#include <biotracker/Registry.h>

extern "C" {
    void registerTracker() {
        BioTracker::Core::Registry::getInstance().registerTrackerType<SobelTracker>("SobelTracker");
    }
}

SobelTracker::SobelTracker(Settings &settings)
    : TrackingAlgorithm(settings)
    , m_toolsFrame(std::make_shared<QFrame>()) {
}

void SobelTracker::track(ulong, const cv::Mat &imgOriginal) {
}

void SobelTracker::paint(ProxyMat &m, const TrackingAlgorithm::View &view)
{

}


void SobelTracker::paintOverlay(QPainter *painter, const View &view) {
}
