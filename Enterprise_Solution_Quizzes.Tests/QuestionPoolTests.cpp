#include "pch.h"
#include "CppUnitTest.h"

#include "QuestionPool.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EnterpriseSolutionQuizzesTests
{
	TEST_CLASS(QuestionPoolTests)
	{
	public:
		TEST_METHOD(save)
		{
			//setup
			QuestionPool pool("Pool1");
			//act
			
			//assert
			Assert::AreEqual(pool.save(0), false);
		}
		TEST_METHOD(load)
		{
			//setup
			QuestionPool pool("Pool1");
			//act

			//assert
			Assert::AreEqual(pool.load(), false);
		}

		TEST_METHOD(Init_name_saved)
		{
			//setup
			QuestionPool pool("Pool1");
			string expected = "Pool1";
			string answer;
			//act
			answer = pool.getID();
			//assert
			Assert::AreEqual(expected, answer);
		}

		TEST_METHOD(addQuestion)
		{
			//setup
			QuestionPool pool("Pool1");
			bool expected = true;
			bool answer;
			//act
			answer = pool.addQuestion("dog", 1);
			//assert
			Assert::AreEqual(expected, answer);
		}
		//TEST_METHOD(addDuplicateQuestion)
		//{
		//	//setup
		//	QuestionPool pool("Pool1");
		//	bool expected = false;
		//	bool answer;
		//	//act
		//	answer = pool.addQuestion("dog", 1);
		//	answer = pool.addQuestion("dog", 1);
		//	//assert
		//	Assert::AreEqual(expected, answer);
		//}

		TEST_METHOD(addOptionToInvalidQuestion)
		{
			//setup
			QuestionPool pool("Pool1");
			bool expected = false;
			bool answer;
			//act
			answer = pool.addOption("dog","cat", 1);

			//assert
			Assert::AreEqual(expected, answer);
		}

		TEST_METHOD(addOptionValidQuestion)
		{
			//setup
			QuestionPool pool("Pool1");
			bool expected = true;
			bool answer;
			//act
			answer = pool.addQuestion("dog", 1);
			answer = pool.addOption("dog", "cat", 1);

			//assert
			Assert::AreEqual(expected, answer);
		}

		TEST_METHOD(deleteInvalidOption)
		{
			//setup
			QuestionPool pool("Pool1");
			bool expected = false;
			bool answer;
			//act

			answer = pool.deleteOption("dog", "cat");

			//assert
			Assert::AreEqual(expected, answer);
		}

		TEST_METHOD(deleteValidOption)
		{
			//setup
			QuestionPool pool("Pool1");
			bool expected = true;
			bool answer;
			//act
			answer = pool.addQuestion("dog", 1);
			answer = pool.addOption("dog", "cat", 1);
			answer = pool.deleteOption("dog", "cat");

			//assert
			Assert::AreEqual(expected, answer);
		}

		TEST_METHOD(setAnswerTrue)
		{
			//setup
			QuestionPool pool("Pool1");
			bool expected = true;
			bool answer;
			//act
			answer = pool.addQuestion("dog", 1);
			answer = pool.addOption("dog", "cat", 0);
			answer = pool.setAnswer("dog", "cat", 1);

			//assert
			Assert::AreEqual(expected, answer);
		}

		TEST_METHOD(setAnswerFalse)
		{
			//setup
			QuestionPool pool("Pool1");
			bool expected = false;
			bool answer;
			//act
			answer = pool.addQuestion("dog", 1);
			answer = pool.addOption("dog", "cat", 1);
			answer = pool.setAnswer("dog", "cat", 0);

			//assert
			Assert::AreEqual(expected, answer);
		}
		TEST_METHOD(getID)
		{
			//setup
			QuestionPool pool("Pool1");
			string expected = "Pool1";
			string answer;
			//act
			answer = pool.getID();
			//assert
			Assert::AreEqual(expected, answer);
		}
		TEST_METHOD(getQuestions)
		{
			//setup
			QuestionPool pool("Pool1");
			std::vector<std::string> expected;
			expected.push_back("dog");
			expected.push_back("cat");
			//act
			pool.addQuestion("dog", 1);
			pool.addQuestion("cat", 1);

			//assert
			std::vector<std::string> answers;
			answers = pool.getQuestions();
			for (int i = 0; i < pool.getQuestions().size(); i++) {
				if (answers.at(i) != expected.at(i)) {
					Assert::Fail();
				}
			}
			Assert::AreEqual(1, 1);
		}
		TEST_METHOD(getQuestionsInvalid)
		{
			//setup
			QuestionPool pool("Pool1");
			std::vector<std::string> questions;
			//act
			questions = pool.getQuestions();

			//assert
			Assert::AreEqual(0, (int)questions.size());
			
		}

		TEST_METHOD(getOptions)
		{
			//setup
			QuestionPool pool("Pool1");
			std::vector<std::string> expected;
			expected.push_back("dog");
			expected.push_back("cat");
			//act
			pool.addQuestion("dog", 1);
			pool.addOption("dog", "dog", 0);
			pool.addOption("dog", "cat", 0);

			//assert
			std::vector<std::string> answers;
			answers = pool.getOptions("dog");
			for (int i = 0; i < pool.getQuestions().size(); i++) {
				if (answers.at(i) != expected.at(i)) {
					Assert::Fail();
				}
			}
			Assert::AreEqual(1, 1);
		}

		TEST_METHOD(getOptionsInvalidQuestion)
		{
			//setup
			QuestionPool pool("Pool1");
			std::vector<std::string> questions;
			//act
			questions = pool.getOptions("dog");

			//assert
			Assert::AreEqual(0, (int)questions.size());

		}
	};
}
