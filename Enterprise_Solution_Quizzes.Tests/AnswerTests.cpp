#include "pch.h"
#include "CppUnitTest.h"

#include "Answer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EnterpriseSolutionQuizzesTests
{
	TEST_CLASS(AnswerTests)
	{
	public:

		TEST_METHOD(init_Answer_title_Saved)
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

		TEST_METHOD(init_Answer_expected_Saved)
		{
			//setup
			answer ans("hello", 1, 0);
			bool expected = true;
			bool answer;
			//act
			answer = ans.getExpected();
			//assert
			Assert::AreEqual(expected, answer);
		}


		TEST_METHOD(init_Answer_QuestionID_Saved)
		{
			//setup
			answer ans("hello", 1, 0);
			int expected = 0;
			int answer;
			//act
			answer = ans.getQuestionID();
			//assert
			Assert::AreEqual(expected, answer);
		}


		TEST_METHOD(select_true_to_false)
		{
			//setup
			answer ans("hello", 1, 0);
			bool expected = false;
			bool answer;
			//act
			answer = ans.select();
			answer = ans.select();
			//assert
			Assert::AreEqual(expected, answer);
		}

		TEST_METHOD(select_false_to_true)
		{
			//setup
			answer ans("hello", 1, 0);
			bool expected = true;
			bool answer;
			//act
			answer = ans.select();
			//assert
			Assert::AreEqual(expected, answer);
		}


		TEST_METHOD(getAnswer)
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

		TEST_METHOD(isCorrectTrue)
		{
			//setup
			answer ans("hello", 1, 0);
			bool expected = true;
			bool answer;
			//act
			answer = ans.select();
			answer = ans.isCorrect();
			//assert
			Assert::AreEqual(expected, answer);
		}


		TEST_METHOD(isCorrectFalse)
		{
			//setup
			answer ans("hello", 1, 0);
			bool expected = false;
			bool answer;
			//act
			answer = ans.isCorrect();
			//assert
			Assert::AreEqual(expected, answer);
		}

		TEST_METHOD(getExpectedTrue)
		{
			//setup
			answer ans("hello", 1, 0);
			bool expected = true;
			bool answer;
			//act
			answer = ans.getExpected();
			//assert
			Assert::AreEqual(expected, answer);
		}

		TEST_METHOD(getExpectedFalse)
		{
			//setup
			answer ans("hello", 0, 0);
			bool expected = false;
			bool answer;
			//act
			answer = ans.getExpected();
			//assert
			Assert::AreEqual(expected, answer);
		}

		TEST_METHOD(getQuestionId)
		{
			//setup
			answer ans("hello", 1, 0);
			int expected = 0;
			int answer;
			//act
			answer = ans.getQuestionID();
			//assert
			Assert::AreEqual(expected, answer);
		}
	};
}
