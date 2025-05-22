#include "Error.h"

//================================================= contructors & destructors =================================================
Error::Error(ContextData* data) : State(data){

}

Error::~Error() {}

//===================================================== private functions =====================================================

void Error::entry() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void Error::exit() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

//===================================================== public functions =====================================================
