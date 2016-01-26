#pragma once

#include <QGroupBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>

#include <biotracker/TrackingAlgorithm.h>

class SobelTracker : public TrackingAlgorithm {
    Q_OBJECT
  public:
    SobelTracker(Settings &settings);

    void track(ulong frameNumber, const cv::Mat &frame) override;
    void paint(ProxyMat &m, View const &view = OriginalView) override;
    void paintOverlay(QPainter *painter, View const &view = OriginalView) override;

  private:
    cv::Mat &m_mat;

};
