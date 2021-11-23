#ifndef ASSERTIONSEXC_H_INCLUDED
#define ASSERTIONSEXC_H_INCLUDED


#include <Util/StackTrace.hpp>
#define ASSERT_TRUE_OR_THROW(condition, message) if (!(condition)) throw EnjoLib::ExceptRuntimeError(STRACE_THROW(message));


#endif // ASSERTIONSEXC_H_INCLUDED
