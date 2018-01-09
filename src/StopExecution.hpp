//
// Created by Kane York on 1/9/18.
//

#ifndef ABSTRACTVM_STOPEXECUTION_HPP
#define ABSTRACTVM_STOPEXECUTION_HPP

#include <exception>
#include <string>

/**
 * Special error to cleanly exit.
 */
class StopExecution : public std::exception {
public:
    StopExecution();
    StopExecution(StopExecution const &src);
    virtual ~StopExecution();
    StopExecution &operator=(StopExecution const &rhs);

    const char * what() const throw();
};


#endif // ABSTRACTVM_STOPEXECUTION_HPP
