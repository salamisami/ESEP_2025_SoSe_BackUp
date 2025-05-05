#ifndef FBM_H
#define FBM_H

#include <memory>
#include <thread>
#include <atomic>
#include <IFBMState.h>

class FBM
{
public:
    FBM();
    ~FBM();
    void transitionTo(std::unique_ptr<IFBMState> state);
    void buttonStartUp(bool pressedLong, bool hasErroOrWarning);
    void buttonStop();

    void startBlinkingThread(double frequency);
    void stopBlinkingThread();

private:
    std::unique_ptr<IFBMState> currentstate_;
    std::thread blinkingThread;
    std::atomic<bool> stopBlinking_{false};
}

#endif
