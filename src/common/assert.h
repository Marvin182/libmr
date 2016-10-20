#ifndef MR_ASSERT_H
#define MR_ASSERT_H

// Using Assert Library by Gregory Pakosz
// https://github.com/gpakosz/Assert

#define PPK_ASSERT_ENABLED 1
#define PPK_ASSERT_DEFAULT_LEVEL Error

#include "pempek_assert.h"

using namespace pempek::assert::implementation;

// ways do deactivate assert macros:
// #define assert_debug(expression, ...) 	do{}while(false)
// #define assert_debug 					PPK_ASSERT_UNUSED

#define assert_warning 			PPK_ASSERT_WARNING 	// Purpose: Something might be wrong but everything should work
#define assert_debug 			PPK_ASSERT_DEBUG 	// Purpose: find bugs
#define assert_error 			PPK_ASSERT_ERROR 	// Purpose: clearly something wrong
#define assert_fatal 			PPK_ASSERT_FATAL 	// Purpose: OMG! Let's pray that we didn't destroy the world

#define assert_unreachable(...)	PPK_ASSERT_FATAL(false, "Reached unexpected code path.")

#ifdef BUILD_WITH_QT

namespace mr {
namespace assert {

const char* levelToStr(int level);
void init();
void setMinExistApplicationLevel(int level);
void addAssertHandler(AssertHandler handler);
void removeAllAsserdHandlers();

} // namespace assert
} // namespace mr

#endif // BUILD_WITH_QT

#endif // MR_ASSERT_H
