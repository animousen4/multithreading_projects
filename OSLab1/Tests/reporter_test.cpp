#include <gtest/gtest.h>
#include "../Reporter/EmployeeSalary.h"

namespace ComponentsOutTesting {

	TEST(EmployeeTest, OstreamEmployeeTest) {
		Employee empl{ 1, "name", 1.0 };

		std::stringstream ss;

		ss << empl;

		EXPECT_EQ(ss.str(), "1\tname\t1");
	}

	TEST(EmployeeSalaryTest, OstreamEmployeeSalaryTest) {
		EmployeeSalary salary{
			Employee{1, "name", 1.0},
			1.0
		};

		std::stringstream ss;

		ss << salary;

		EXPECT_EQ(ss.str(), "1\tname\t1\t1");
	}
}
