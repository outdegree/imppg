/*
ImPPG (Image Post-Processor) - common operations for astronomical stacks and other images
Copyright (C) 2016-2024 Filip Szczerek <ga.software@yahoo.com>

This file is part of ImPPG.

ImPPG is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

ImPPG is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with ImPPG.  If not, see <http://www.gnu.org/licenses/>.

File description:
    Assert and abort macros.
*/

#ifndef ImPPG_ASSERT_H
#define ImPPG_ASSERT_H

#include "common/dirs.h"

#include <cstdlib>
#include <fstream>
#include <wx/datetime.h>

#define CRASH_LOG \
    std::ofstream{GetUserDataDir() / "imppg-crash.log", std::ios_base::app} \
        << wxDateTime::Now().FormatISOCombined()                            \
        << " "

#define IMPPG_ASSERT(condition)                                              \
{                                                                            \
    if (!(condition))                                                        \
    {                                                                        \
        { CRASH_LOG << "Assertion failed at " << __FILE__ << ":" << __LINE__ \
                << " inside " << __FUNCTION__ << "\n"                        \
                << "Condition: " << #condition << "\n"; }                    \
        std::abort();                                                        \
    }                                                                        \
}

#define IMPPG_ASSERT_MSG(condition, msg)                      \
{                                                             \
    if (!(condition))                                         \
    {                                                         \
        { CRASH_LOG << "Assertion failed: " << msg << "\n"; } \
        std::abort();                                         \
    }                                                         \
}


#define IMPPG_ABORT()                                                                 \
{                                                                                     \
    { CRASH_LOG << "Abnormal program state detected: " << __FILE__ << ":" << __LINE__ \
        << " inside " << __FUNCTION__ << "\nExiting.\n"; }                            \
    std::abort();                                                                     \
}

#define IMPPG_ABORT_MSG(msg)                                            \
{                                                                       \
    { CRASH_LOG << __FILE__ << ":" << __LINE__                          \
                << " inside " << __FUNCTION__ << ": " << msg << "\n"; } \
    std::abort();                                                       \
}

#endif // ImPPG_ASSERT_H
