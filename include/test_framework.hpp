// Native C++ test framework header
#ifndef TEST_FRAMEWORK_HPP
#define TEST_FRAMEWORK_HPP

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <sstream>

class TestFramework {
private:
    struct TestCase {
        std::string name;
        std::function<void()> test;
    };

    static std::vector<TestCase>& getTests() {
        static std::vector<TestCase> tests;
        return tests;
    }

public:
    static void registerTest(const std::string& name, std::function<void()> test) {
        getTests().push_back({name, test});
    }

    static int runAllTests() {
        int passed = 0;
        int failed = 0;

        std::cout << "\n========== Running Tests ==========\n" << std::endl;

        for (const auto& test : getTests()) {
            try {
                test.test();
                std::cout << "✓ " << test.name << std::endl;
                passed++;
            } catch (const std::exception& e) {
                std::cout << "✗ " << test.name << std::endl;
                std::cout << "  Error: " << e.what() << std::endl;
                failed++;
            } catch (...) {
                std::cout << "✗ " << test.name << std::endl;
                std::cout << "  Error: Unknown exception" << std::endl;
                failed++;
            }
        }

        std::cout << "\n==================================\n";
        std::cout << "Tests passed: " << passed << "\n";
        std::cout << "Tests failed: " << failed << "\n";
        std::cout << "Total tests:  " << (passed + failed) << "\n";
        std::cout << "==================================\n" << std::endl;

        return (failed == 0) ? 0 : 1;
    }
};

#define ASSERT_TRUE(condition) \
    if (!(condition)) { \
        throw std::runtime_error(std::string("Assertion failed: ") + #condition); \
    }

#define ASSERT_FALSE(condition) \
    if ((condition)) { \
        throw std::runtime_error(std::string("Assertion failed: !") + #condition); \
    }

#define ASSERT_EQ(expected, actual) \
    if ((expected) != (actual)) { \
        std::ostringstream oss; \
        oss << "Expected: " << (expected) << ", Got: " << (actual); \
        throw std::runtime_error(oss.str()); \
    }

#define ASSERT_NE(val1, val2) \
    if ((val1) == (val2)) { \
        throw std::runtime_error(std::string("Values should not be equal")); \
    }

#define ASSERT_THROW(statement) \
    try { \
        statement; \
        throw std::runtime_error("Expected exception but none was thrown"); \
    } catch (const std::exception&) { \
        /* Expected */ \
    }

#define ASSERT_NO_THROW(statement) \
    try { \
        statement; \
    } catch (const std::exception& e) { \
        throw std::runtime_error(std::string("Unexpected exception: ") + e.what()); \
    }

#define EXPECT_TRUE(condition) \
    if (!(condition)) { \
        std::cerr << "  Warning: Expectation failed: " << #condition << std::endl; \
    }

#define EXPECT_FALSE(condition) \
    if ((condition)) { \
        std::cerr << "  Warning: Expectation failed: !" << #condition << std::endl; \
    }

#define EXPECT_EQ(expected, actual) \
    if ((expected) != (actual)) { \
        std::cerr << "  Warning: Expected: " << (expected) << ", Got: " << (actual) << std::endl; \
    }

#define EXPECT_NE(val1, val2) \
    if ((val1) == (val2)) { \
        std::cerr << "  Warning: Values should not be equal" << std::endl; \
    }

#define TEST(testName) \
    void test_##testName(); \
    struct Register_##testName { \
        Register_##testName() { \
            TestFramework::registerTest(#testName, test_##testName); \
        } \
    } register_##testName; \
    void test_##testName()

#endif // TEST_FRAMEWORK_HPP
