#include "Mailbox.h"

//================================================= contructors & destructors =================================================
template <typename T>
Mailbox<T>::Mailbox(uint8_t mailbox_size) {
    int initVacant = sem_init(&vacant, 0, mailbox_size);
    int initOccupied = sem_init(&occupied, 0, 0);

    if(initVacant == -1 || initOccupied == -1) {
        THROW("Failed to initialize Semaphores in ThreadSafeQueue");
    }
}
template <typename T>
Mailbox<T>::~Mailbox() {
    mtx.lock();
    sem_destroy(&vacant);
    sem_destroy(&occupied);
    mtx.unlock();
}



//===================================================== private functions =====================================================

//void Mailbox::privateFunction(){}

//===================================================== public functions =====================================================

template<typename T>
void Mailbox<T>::put(T element) {
    sem_wait(&vacant);
    mtx.lock();
    this->element = element;
    mtx.unlock();
    sem_post(&occupied);
}

template<typename T>
T Mailbox<T>::take() {
    sem_wait(&occupied);
    mtx.lock();
    T element = this->element;
    mtx.unlock();
    sem_post(&vacant);
    return element;
}