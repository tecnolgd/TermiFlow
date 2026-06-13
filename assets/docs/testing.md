# Unit Testing Guide for TermiFlow

## Overview
This project uses a **native C++ test framework** (no external dependencies). Tests cover:
- System statistics (CPU, memory, uptime)
- Theme management and validation
- Command parsing and tokenization
- Command validation logic

## Prerequisites

**No extra installation required!** The test framework is built-in and has zero external dependencies apart from the tool [prerequisites](../../README.md#prerequisites)

## Running Tests

### Using Make:
```bash
make test      # Build and run all unit tests
```
### Two step way

1. 
    ```bash
    make #or 'make windows' for windows OS
    ```
2.  ```bash
    ./build/test_runner
    ```

The test runner automatically discovers and executes all tests in the `tests/` directory.

## Test Structure

Tests are organized by module:
- `system_stats_test.cpp` - Tests for system statistics (4 tests)
- `theme_manager_test.cpp` - Tests for theme validation (3 tests)
- `command_parsing_test.cpp` - Tests for command tokenization (5 tests)
- `main_test.cpp` - Test runner entry point

## Test Coverage

| Module | Tests | Status |
|--------|-------|--------|
| SystemStats | 4 | ✓ |
| ThemeManager | 3 | ✓ |
| CommandParsing | 5 | ✓ |
| **Total** | **12** | **✓** |

## Example Test Output

```
========== Running Tests ==========

✓ Command_TokenizesSimpleCommand
✓ Command_TokenizesMultipleArguments
✓ Command_HandlesEmptyInput
✓ Command_HandlesExtraWhitespace
✓ CommandValidation_RecognizesValidCommands
✓ SystemStats_GetCPUUsageReturnsString
✓ SystemStats_GetMemoryUsageReturnsValidString
✓ SystemStats_GetUptimeReturnsValidString
✓ SystemStats_StatsInteractiveDoesNotCrash
✓ Theme_ValidThemeNamesAccepted
✓ Theme_InvalidThemeNamesRejected
✓ Theme_CaseSensitivity

==================================
Tests passed: 12
Tests failed: 0
Total tests:  12
==================================
```

## Adding New Tests

1. Create a new test file in `tests/` directory with `_test.cpp` suffix
2. Include test framework header: `#include "test_framework.hpp"`
3. Write test cases using the `TEST()` macro
4. Tests will be automatically discovered and run with `make test`

Example:
```cpp
#include "test_framework.hpp"

TEST(MyModule_TestDescription) {
    // Arrange
    int result = myFunction();
    
    // Assert
    ASSERT_EQ(result, expected_value);
}
```

## Assertion Macros

### Fatal Assertions (stop test on failure)
- `ASSERT_TRUE(condition)` - Check if condition is true
- `ASSERT_FALSE(condition)` - Check if condition is false
- `ASSERT_EQ(expected, actual)` - Check equality
- `ASSERT_NE(val1, val2)` - Check inequality
- `ASSERT_THROW(statement)` - Check if exception is thrown
- `ASSERT_NO_THROW(statement)` - Check if no exception is thrown

### Warning Assertions (continue on failure)
- `EXPECT_TRUE(condition)` - Check if condition is true
- `EXPECT_FALSE(condition)` - Check if condition is false
- `EXPECT_EQ(expected, actual)` - Check equality
- `EXPECT_NE(val1, val2)` - Check inequality


- `EXPECT_EQ(a, b)` - Equal
- `EXPECT_NE(a, b)` - Not equal
- `EXPECT_TRUE(condition)` - True
- `EXPECT_FALSE(condition)` - False
- `EXPECT_THROW(statement, exception_type)` - Throws exception
- `EXPECT_NO_THROW(statement)` - Does not throw