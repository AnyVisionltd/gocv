#include "video.h"
#if defined(HAVE_OPENCV_VIDEO) && !defined(DISABLE_OPENCV_VIDEO)

BackgroundSubtractorMOG2 BackgroundSubtractorMOG2_Create() {
    return new cv::Ptr<cv::BackgroundSubtractorMOG2>(cv::createBackgroundSubtractorMOG2());
}

BackgroundSubtractorMOG2 BackgroundSubtractorMOG2_CreateWithParams(int history, double varThreshold, bool detectShadows) {
    return new cv::Ptr<cv::BackgroundSubtractorMOG2>(cv::createBackgroundSubtractorMOG2(history,varThreshold,detectShadows));
}

BackgroundSubtractorKNN BackgroundSubtractorKNN_Create() {
    return new cv::Ptr<cv::BackgroundSubtractorKNN>(cv::createBackgroundSubtractorKNN());
}

BackgroundSubtractorKNN BackgroundSubtractorKNN_CreateWithParams(int history, double dist2Threshold, bool detectShadows) {
    return new cv::Ptr<cv::BackgroundSubtractorKNN>(cv::createBackgroundSubtractorKNN(history,dist2Threshold,detectShadows));
}

void BackgroundSubtractorMOG2_Close(BackgroundSubtractorMOG2 b) {
    delete b;
}

void BackgroundSubtractorMOG2_Apply(BackgroundSubtractorMOG2 b, Mat src, Mat dst) {
    (*b)->apply(*src, *dst);
}

void BackgroundSubtractorKNN_Close(BackgroundSubtractorKNN k) {
    delete k;
}

void BackgroundSubtractorKNN_Apply(BackgroundSubtractorKNN k, Mat src, Mat dst) {
    (*k)->apply(*src, *dst);
}

void CalcOpticalFlowFarneback(Mat prevImg, Mat nextImg, Mat flow, double scale, int levels,
                              int winsize, int iterations, int polyN, double polySigma, int flags) {
    cv::calcOpticalFlowFarneback(*prevImg, *nextImg, *flow, scale, levels, winsize, iterations, polyN,
                                 polySigma, flags);
}

void CalcOpticalFlowPyrLK(Mat prevImg, Mat nextImg, Mat prevPts, Mat nextPts, Mat status, Mat err) {
    cv::calcOpticalFlowPyrLK(*prevImg, *nextImg, *prevPts, *nextPts, *status, *err);
}

void CalcOpticalFlowPyrLKWithParams(Mat prevImg, Mat nextImg, Mat prevPts, Mat nextPts, Mat status, Mat err, Size winSize, int maxLevel, TermCriteria criteria, int flags, double minEigThreshold){
    cv::Size sz(winSize.width, winSize.height);
    cv::calcOpticalFlowPyrLK(*prevImg, *nextImg, *prevPts, *nextPts, *status, *err, sz, maxLevel, *criteria, flags, minEigThreshold);
}

#ifdef HAVE_OPENCV_TRACKING

bool Tracker_Init(Tracker self, Mat image, Rect boundingBox) {
    cv::Rect bb(boundingBox.x, boundingBox.y, boundingBox.width, boundingBox.height);

    (*self)->init(*image, bb);
    return true;
}

bool Tracker_Update(Tracker self, Mat image, Rect* boundingBox) {
    cv::Rect bb;
    bool ret = (*self)->update(*image, bb);
    boundingBox->x = int(bb.x);
    boundingBox->y = int(bb.y);
    boundingBox->width = int(bb.width);
    boundingBox->height = int(bb.height);
    return ret;
}

TrackerMIL TrackerMIL_Create() {
    return new cv::Ptr<cv::TrackerMIL>(cv::TrackerMIL::create());
}

void TrackerMIL_Close(TrackerMIL self) {
    delete self;
}
#endif
#endif