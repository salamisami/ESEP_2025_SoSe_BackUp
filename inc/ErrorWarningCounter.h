#ifndef ERRORWARNINGCOUNTER_H
#define ERRORWARNINGCOUNTER_H

class ErrorWarningCounter{
    public:

    ErrorWarningCounter();
    virtual ~ErrorWarningCounter() = default;

    bool is_error_or_warning();

    void error_or_warning_occured();
    void error_or_warning_resolved();

    private:

    int error_warning_count;
};
#endif
