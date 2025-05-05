#ifndef FBM_H
#define FBM_H

#include <memory>

class FBM
{
public:
    FBM();
    ~FBM();
    void transitionTo(std::unique_ptr<IBMState> state);
    void buttonStartUp(bool pressedLong, bool hasErroOrWarning);
    void buttonStop();

    void startBlinkingThread(double frequency);
    void stopBlinkingThread();

private:
    std::unique_ptr<IFBMState> currentstate_;
}

#endif FBM_H