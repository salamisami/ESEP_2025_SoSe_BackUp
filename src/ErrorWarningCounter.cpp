#include "ErrorWarningCounter.h"
#include <cstdio>
#include <stdlib.h>

ErrorWarningCounter::ErrorWarningCounter(){
    error_warning_count = 0;
}


bool ErrorWarningCounter::is_error_or_warning(){
    if(error_warning_count > 0){
        return true;
    }
    if(error_warning_count == 0){
        return false;
    }
    else
    {
        //Fehler im System, weil der ErrorCounter nicht Richtig gesetzt wird
        perror("error_warning hat einen unerwarteten Wert: ");
        printf("%d\n", error_warning_count);
        return true;
    }
}

void ErrorWarningCounter::error_or_warning_occured(){
    error_warning_count++;
}

void ErrorWarningCounter::error_or_warning_resolved(){
    error_warning_count--;
}
