#include <gtest/gtest.h>
#include "../Reporter/EmployeeSalary.h"
#include "../Reporter/NegativeNumberException.h"
#include "../Reporter/SalaryCalculator.h"
namespace SalaryCalculatorTesting {
	TEST(SalaryCalculatorTest, SalaryCalculatorTestCaseFiveHour) {
		Employee empl{ 1, "name", 1.0 };
		SalaryCalculator salaryCalculator;

		EmployeeSalary calcSalary = salaryCalculator.calculateSalary(empl, 5);

		EXPECT_EQ(calcSalary.salary, 5);
	}

	TEST(SalaryCalculatorTest, SalaryCalculatorTestCaseZeroHour) {
		Employee empl{ 1, "name", 7.3 };

		SalaryCalculator salaryCalculator;

		EmployeeSalary calcSalary = salaryCalculator.calculateSalary(empl, 0);

		EXPECT_EQ(calcSalary.salary, 0);
	}

	TEST(SalaryCalculatorTest, SalaryCalculatorTestNegativeNumberException) {
		Employee empl{ 1, "name", 2.453 };

		SalaryCalculator salaryCalculator;
		try {
			salaryCalculator.calculateSalary(empl, -4);
		}
		catch (const std::runtime_error& e) {
			EXPECT_STREQ(e.what(), "Should be > 0");
		}
		
	}

}
