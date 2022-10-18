#include "pch.h"
#include "CppUnitTest.h"

#include "Answer.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EnterpriseSolutionQuizzesTests
{
	TEST_CLASS(EnterpriseSolutionQuizzesTests)
	{
	public:
		
		TEST_METHOD(init_answer_answer_set)
		{
			//setup
			answer ans("hello", 1, 0);
			string expected = "hello";
			string answer;
			//act
			answer = ans.getAnswer();
			//assert
			Assert::AreEqual(expected, answer);
		}
	};
}
