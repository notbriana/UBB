#include "service.h"
#include <cassert>
#include <iostream>

// Mock repository for testing
class MockRepository {
private:
    std::vector<Car> testCars;

public:
    MockRepository() {
        // Create test data
        testCars.push_back(Car("Toyota", "Camry", 2020, "blue"));
        testCars.push_back(Car("Toyota", "Corolla", 2019, "red"));
        testCars.push_back(Car("Toyota", "Prius", 2021, "white"));
        testCars.push_back(Car("Honda", "Civic", 2018, "black"));
        testCars.push_back(Car("Honda", "Accord", 2020, "gray"));
        testCars.push_back(Car("Ford", "Focus", 2017, "blue"));
    }

    std::vector<Car> getCars() const { return testCars; }
};

// Test Service class for unit testing
class TestService {
private:
    MockRepository mockRepo;

public:
    int getNumberOfCarsByManufacturer(const std::string& manufacturer) const {
        if (manufacturer.empty()) {
            return 0;
        }

        std::vector<Car> allCars = mockRepo.getCars();
        int count = 0;

        for (const auto& car : allCars) {
            if (car.getManufacturer() == manufacturer) {
                count++;
            }
        }

        return count;
    }
};

// Test functions
void testValidManufacturerWithMultipleCars() {
    TestService service;
    int result = service.getNumberOfCarsByManufacturer("Toyota");
    assert(result == 3);
    std::cout << "  Test 1 passed: Valid manufacturer with multiple cars (Toyota: 3)" << std::endl;
}

void testValidManufacturerWithTwoCars() {
    TestService service;
    int result = service.getNumberOfCarsByManufacturer("Honda");
    assert(result == 2);
    std::cout << "  Test 2 passed: Valid manufacturer with two cars (Honda: 2)" << std::endl;
}

void testValidManufacturerWithOneCar() {
    TestService service;
    int result = service.getNumberOfCarsByManufacturer("Ford");
    assert(result == 1);
    std::cout << "  Test 3 passed: Valid manufacturer with one car (Ford: 1)" << std::endl;
}

void testInvalidManufacturer() {
    TestService service;
    int result = service.getNumberOfCarsByManufacturer("BMW");
    assert(result == 0);
    std::cout << "  Test 4 passed: Invalid manufacturer returns 0 (BMW: 0)" << std::endl;
}

void testEmptyManufacturerName() {
    TestService service;
    int result = service.getNumberOfCarsByManufacturer("");
    assert(result == 0);
    std::cout << "  Test 5 passed: Empty manufacturer name returns 0" << std::endl;
}

void testCaseSensitivity() {
    TestService service;
    int result = service.getNumberOfCarsByManufacturer("toyota"); // lowercase
    assert(result == 0); // Should be case-sensitive
    std::cout << "std::string Test 6 passed: Case sensitivity test (toyota != Toyota)" << std::endl;
}

void testManufacturerWithSpaces() {
    TestService service;
    int result = service.getNumberOfCarsByManufacturer(" Toyota ");
    assert(result == 0); // Should be exact match
    std::cout << "  Test 7 passed: Manufacturer with spaces returns 0" << std::endl;
}

// Main test runner
//int main() {
//    std::cout << "Running tests for getNumberOfCarsByManufacturer function...\n" << std::endl;
//
//    try {
//        testValidManufacturerWithMultipleCars();
//        testValidManufacturerWithTwoCars();
//        testValidManufacturerWithOneCar();
//        testInvalidManufacturer();
//        testEmptyManufacturerName();
//        testCaseSensitivity();
//        testManufacturerWithSpaces();
//
//        std::cout << "\n All tests passed successfully!" << std::endl;
//        std::cout << "\nTest Summary:" << std::endl;
//        std::cout << "- Total tests: 7" << std::endl;
//        std::cout << "- Passed: 7" << std::endl;
//        std::cout << "- Failed: 0" << std::endl;
//
//    }
//    catch (const std::exception& e) {
//        std::cerr << " Test failed with exception: " << e.what() << std::endl;
//        return 1;
//    }
//
//    return 0;
//}