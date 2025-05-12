/*
 * Copyright (c) 2004-2005, Swedish Institute of Computer Science.
 * All rights reserved.
 * Copyright (c) 2025, Marco Bacchi <marco@bacchi.at>
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *         Marco Bacchi <marco@bacchi.at>
 */

/*!
    \file   pt.h

    \brief Protothread definitions for MyOs.

    \details
    Protothreads are a lightweight, stackless threading mechanism, offering
    a way to implement non-blocking code in a blocking manner, which is
    particularly useful in resource-constrained systems like embedded devices.
    This implementation is based on Contiki 2.7 protothread but has been adapted
    and extended for use in myos.

    Protothreads provide a way to perform tasks in threads without using multiple
    stacks. This is achieved through the use of local continuations that save
    and restore the execution state of a function at specific points.

    Local continuations in this implementation are based on Duff's device, a
    technique for creating a coroutine in C.

    Protothreads are particularly effective in event-driven systems where tasks do
    not need to be executed simultaneously but rather wait for specific events or
    conditions to proceed. They offer a simple and memory-efficient mechanism
    for implementing cooperative multitasking.

    \note Protothreads do not save the call stack, thus local variables are not
    preserved across blocking calls. Care must be taken to preserve the state
    across yields or waits if needed.
*/

#ifndef PT_H_
#define PT_H_

#include <stdint.h>


/*!
    \brief Typedef for local continuation state.

    \details This type is used to store the state of a protothread. It should
    be capable of storing at least as many different values as there are lines
    in the function that uses the protothread.
*/
typedef uint16_t lc_t;


/*!
    \brief Definitions and macros for local continuations used in protothreads.

    \details Local continuations provide a lightweight mechanism to preserve the
    state of a function such that it can be resumed later. This is particularly useful
    in implementing protothreads for cooperative multitasking in a memory-constrained
    environment.
*/
/*!\{*/

/*!
    \brief Initialize a local continuation.

    \param s The local continuation state variable.

    \details This macro initializes the local continuation state, effectively
    setting the protothread to start from its beginning upon the next invocation.
*/
#define LC_INIT(s) s = 0;

/*!
    \brief Default value for an uninitialized or reset local continuation.

    \details This value is used to indicate that the local continuation is either
    uninitialized or has been reset to its initial state.
*/
#define LC_DEFAULT ((lc_t)(~((lc_t)(0))))

/*!
    \brief Value indicating a protothread's termination.

    \details This value is used to indicate that the local continuation has been
    set to its terminated state, either when the protothread terminates via `PT_EXIT`
    or reaches the end of its execution with `PT_END`.
*/
#define LC_SET_DEFAULT(s) s = LC_DEFAULT

/*!
    \brief Resume a local continuation from its last state.

    \param s The local continuation state variable.

    \details This macro is used at the beginning of a protothread function to
    resume execution from the point where the protothread was last suspended.
*/
#define LC_RESUME(s) switch(s) { case 0:

/*!
    \brief Set the local continuation to the current line number.

    \param s The local continuation state variable.

    \details This macro is used within a protothread to mark the point to which
    control should return the next time the protothread is resumed.
*/
#define LC_SET(s) s = __LINE__; case __LINE__:

/*!
    \brief Set the local continuation to the current line number and yield with a return value.

    \param s The local continuation state variable.
    \param retval The return value when yielding.

    \details This macro is similar to LC_SET but also allows the protothread to
    yield execution and return a value. This is useful for implementing blocking operations within a protothread.
*/
#define LC_SET_YIELD(s,retval) s = __LINE__; return retval; case __LINE__:

/*!
    \brief End the local continuation block.

    \param s The local continuation state variable.

    \details This macro ends the block of code started by LC_RESUME. It should be
    placed at the end of the protothread function.
*/
#define LC_END(s) default:;}

/*!\}*/


/*!
    \brief Struct for managing protothreads.

    \details The `pt_t` structure is used to represent a protothread. Protothreads provide
    a lightweight, stackless means of managing concurrency, particularly useful in memory-constrained
    systems such as embedded devices.

    Each protothread has its own execution context, represented by an instance
    of this structure. The context does not include stack data, making
    protothreads an extremely memory-efficient form of multitasking.

    \see lc_t for the type of the local continuation state variable.

*/
typedef struct {
    lc_t lc; //!< The local continuation state.
} pt_t;


typedef uint8_t ptstate_t; //!< Represents the state of a protothread

/*!
    \brief Protothread state definitions and macros.

    \details This set of macros define various states and conditions of protothreads
    used to control the flow of execution in a protothread.
*/
/*!\{*/


/*!
    \brief Initialized state of a protothread.

    This macro defines the initial state value of a protothread.
*/
#define PT_STATE_INITIALIZED    0

/*!
    \brief Indicates that the protothread is waiting for an event or condition.

    \details This state is used to signify that a protothread is in a waiting state,
    typically used in conjunction with PT_WAIT__ macros to yield control until
    a specific condition is met or an event occurs.
*/
#define PT_STATE_WAITING        1
#define PT_STATE_RUNNING        PT_STATE_WAITING

/*!
    \brief Represents a terminated state of a protothread.

    \details This state is used to indicate that a protothread has completed its execution.
    It is the end state for a protothread and signifies that no further execution
    will take place in this protothread.
*/
#define PT_STATE_TERMINATED     2

/*!\}*/

/*!
    \brief Macro to check if a protothread is currently running.

    \details This macro evaluates to true if the protothread is currently active and
    has not reached its terminated state. It checks if the local continuation
    state (`lc`) is neither in its initial value nor in the default termination
    value, indicating that the protothread is in the midst of its execution.

    \param pt A pointer to the protothread control structure.

*/
#define PT_IS_RUNNING(pt) ( ((pt)->lc > 0) && ((pt)->lc != LC_DEFAULT) )

#define PT_GET_STATE(pt) (((pt)->lc==0)?PT_STATE_INITIALIZED:(((pt)->lc==LC_DEFAULT)?PT_STATE_TERMINATED:PT_STATE_WAITING))

/*!
    \brief Initialize a protothread.

    \details This macro initializes the protothread's local continuation state.
    It should be called before the protothread is first scheduled to run.

    \param pt A pointer to the protothread control structure.
*/
#define PT_INIT(pt) LC_INIT((pt)->lc)

/*!
    \brief Declaration of a protothread.

    \details This macro declares a new protothread. The protothread is implemented as a C function
    that returns a `ptstate_t`. This macro should be placed at the start of the function
    that defines the protothread.

    \param name_args The name and arguments of the C function implementing the protothread.
*/
#define PT_THREAD(name_args) ptstate_t name_args

/*!
    \brief Start a protothread.

    \details This macro marks the beginning of a protothread. It should be placed
    at the start of the protothread function. It sets up the protothread
    to resume execution at the correct position using the local continuation state.

    \param pt A pointer to the protothread control structure.
*/
#define PT_BEGIN(pt) LC_RESUME((pt)->lc)

/*!
    \brief End a protothread.

    \details This macro marks the end of a protothread. It should be placed at the end
    of the protothread function. It sets the protothread's state to terminated
    and returns the termination state.

    \param pt A pointer to the protothread control structure.

*/
#define PT_END(pt) LC_SET_DEFAULT((pt)->lc); LC_END((pt)->lc); return PT_STATE_TERMINATED




/*!
    \brief Block and wait until a condition becomes true.

    \param pt A pointer to the protothread control structure.
    \param condition The condition on which the protothread should wait.

    \details This macro is used to block the execution of a protothread until a specified
    condition is met. The protothread yields and will be resumed at this point when
    it is next scheduled for execution. If the condition is false, the protothread
    returns `PT_STATE_WAITING`, indicating it is waiting for the condition to become true.
*/
#define PT_WAIT_UNTIL(pt, condition)    \
  do {                                  \
    LC_SET((pt)->lc);                   \
    if(!(condition)) {                  \
      return PT_STATE_WAITING;          \
    }                                   \
  } while(0)

/*!
    \brief Block and wait while a condition is true.

    \param pt A pointer to the protothread control structure.
    \param cond The condition on which the protothread should continue waiting.

    \details This macro is used to block the execution of a protothread as long as the specified
    condition is true. The protothread yields and will resume at this point when it is next
    scheduled for execution. The protothread remains in the `PT_STATE_WAITING` state until
    the condition becomes false.

    \note This macro is essentially the inverse of `PT_WAIT_UNTIL`, causing the protothread to
    wait as long as the condition is true rather than waiting for it to become true.
*/
#define PT_WAIT_WHILE(pt, cond)  PT_WAIT_UNTIL((pt),!(cond))


/*!
    \brief Block and wait until a child protothread completes.

    \details This macro is used within a protothread to wait for the completion of a child protothread.
    The parent protothread (the one using this macro) is blocked until the specified child
    protothread has terminated. The child protothread is scheduled and executed in the meantime.

    \param pt A pointer to the protothread control structure.
    \param thread The child protothread to be waited on.

    The macro `PT_SCHEDULE` is used to schedule and run the child protothread. The parent
    protothread remains in the `PT_STATE_WAITING` state as long as the child protothread
    is running.

    \note It is important to ensure that the child protothread is properly initialized
    before using this macro to wait for it.
*/
#define PT_WAIT_THREAD(pt, thread) PT_WAIT_WHILE((pt), PT_SCHEDULE(thread) != PT_STATE_TERMINATED)


/*!
    \brief Spawn a child protothread and wait until it exits.

    \details This macro is used to start (or spawn) a child protothread within the context of a parent
    protothread. The macro initializes the child protothread and then waits for it to complete
    its execution. The parent protothread is blocked until the child protothread terminates.

    The macro combines `PT_INIT` to initialize the child protothread, and `PT_WAIT_THREAD` to
    wait for the child protothread to finish. This is commonly used for structured concurrency
    where the parent protothread needs to perform some action after the child protothread
    completes.

    \param pt A pointer to the protothread control structure of the parent protothread.
    \param child A pointer to the protothread control structure of the child protothread.
    \param thread The child protothread to be executed.
*/
#define PT_SPAWN(pt, child, thread)     \
  do {                                  \
    PT_INIT((child));                   \
    PT_WAIT_THREAD((pt), (thread));     \
  } while(0)


/*!
    \brief Exit the protothread.

    \details This macro causes the protothread to exit. It sets the local continuation state
    to its default termination state and returns `PT_STATE_TERMINATED`, indicating that
    the protothread has completed its execution.

    This macro is typically used to voluntarily terminate a protothread from within its
    code, often as a response to certain conditions being met, or when the protothread has
    completed its intended task.

    \param pt A pointer to the protothread control structure.
*/
#define PT_EXIT(pt)             \
  do {                          \
    LC_SET_DEFAULT((pt)->lc);   \
    return PT_STATE_TERMINATED; \
  } while(0)

/*!
    \brief Schedule a protothread for execution.

    \details This macro is used to schedule a protothread for execution. It calls the
    function that implements the protothread and returns its state. The state
    indicates whether the protothread is still running or has terminated.

    The macro is a simple wrapper that directly calls the protothread function.
    It is used to make the code that schedules protothreads more readable and
    consistent.

    \param f The call to the C function implementing the protothread.
*/
#define PT_SCHEDULE(f) (f)

/*!
    \brief Yield from the current protothread.

    \details This macro yields the execution of the current protothread, allowing other
    processing to take place in the system. The protothread pauses its execution
    and can be resumed later from this point. When the protothread is resumed,
    it continues execution from the statement following the `PT_YIELD`.

    This is particularly useful for cooperative multitasking, where each
    protothread voluntarily yields control periodically to allow other
    protothreads to run.

    \param pt A pointer to the protothread control structure.


*/
#define PT_YIELD(pt)                            \
    do {                                        \
        LC_SET_YIELD((pt)->lc, PT_STATE_WAITING);     \
    } while(0)


/*!
    \brief Yield from the protothread until a condition is true.

    \details This macro yields the protothread, allowing other processing to take place,
    and will only resume the protothread when the specified condition becomes true.
    The condition is evaluated each time the protothread is scheduled to run. If
    the condition is false, the protothread yields again.

    This is useful when a protothread needs to wait for an external event or
    condition without blocking the entire system. The protothread will continue
    executing from the point of yield once the condition is met.

    \param pt A pointer to the protothread control structure.
    \param cond The condition that must become true to resume the protothread.

*/
#define PT_YIELD_UNTIL(pt, cond)                    \
    do {                                            \
        LC_SET_YIELD((pt)->lc, PT_STATE_WAITING);   \
    } while(!(cond))



#endif /* PT_H_ */


