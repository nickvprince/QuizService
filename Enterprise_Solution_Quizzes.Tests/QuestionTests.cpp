#include "pch.h"
#include "CppUnitTest.h"

#include "Question.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EnterpriseSolutionQuizzesTests
{
	TEST_CLASS(QuestionTests)
	{
	public:
		TEST_METHOD(Init_Question_Saved)
		{
			//setup
			question ques("hello", 1);
			string expected = "hello";
			string answer;
			//act
			answer = ques.getQuestion();
			//assert
			Assert::AreEqual(expected, answer);
		}

		TEST_METHOD(Init_points_saved)
		{
			//setup
			question ques("hello", 1);
			int expected = 1;
			int answer;
			//act
			answer = ques.getPoints();
			//assert
			Assert::AreEqual(expected, answer);
		}

		TEST_METHOD(addAnswer)
		{
			//setup
			question ques("hello", 1);
			bool expected = true;
			bool answer;
			//act
			answer = ques.addAnswer("dog", 1);
			//assert
			Assert::AreEqual(expected, answer);
		}

		TEST_METHOD(deleteAnswerExists)
		{
			//setup
			question ques("hello", 1);
			bool expected = true;
			bool answer;
			//act
			answer = ques.addAnswer("dog", 1);
			answer = ques.deleteAnswer("dog");
			//assert
			Assert::AreEqual(expected, answer);
		}

		TEST_METHOD(deleteAnswerNotExists)
		{
			//setup
			question ques("hello", 1);
			bool expected = false;
			bool answer;
			//act
			answer = ques.deleteAnswer("dog");
			//assert
			Assert::AreEqual(expected, answer);
		}

		TEST_METHOD(getPointsEarnedOneCorrectMultipleChoice)
		{
			//setup
			question ques("hello", 1);
			int expected = 1;
			int answer;
			//act
			answer = ques.addAnswer("dog", 1);
			answer = ques.selectAnswer("dog");
			answer = ques.getPointsEarned();
			//assert
			Assert::AreEqual(expected, answer);
		}

		TEST_METHOD(getPointsEarnedOneCorrectMultipleAnswer)
		{
			//setup
			question ques("hello", 1);
			int expected = 0.5;
			int answer;
			//act
			answer = ques.addAnswer("dog", 1);
			answer = ques.addAnswer("cat", 1);
			answer = ques.selectAnswer("dog");
			answer = ques.getPointsEarned();
			//assert
			Assert::AreEqual(expected, answer);
		}

		TEST_METHOD(getPointsEarnedAllCorrectAndOneIncorrect)
		{
			//setup
			question ques("hello", 1);
			int expected = 0.66;
			int answer;
			//act
			answer = ques.addAnswer("dog", 1);
			answer = ques.addAnswer("cat", 1);
			answer = ques.addAnswer("blue", 0);
			answer = ques.selectAnswer("dog");
			answer = ques.selectAnswer("cat");
			answer = ques.selectAnswer("blue");
			answer = ques.getPointsEarned();
			//assert
			Assert::AreEqual(expected, answer);
		}

		TEST_METHOD(getTypeMultipleAnswer)
		{
			//setup
			question ques("hello", 1);
			int expected = 1;
			int answer;
			//act
			answer = ques.addAnswer("dog", 1);
			answer = ques.addAnswer("cat", 1);
			answer = ques.addAnswer("blue", 0);
			answer = ques.getType();
			//assert
			Assert::AreEqual(expected, answer);
		}
		TEST_METHOD(getTypeMultipleQuestion)
		{
			//setup
			question ques("hello", 1);
			int expected = 0;
			int answer;
			//act
			answer = ques.addAnswer("dog", 1);
			answer = ques.addAnswer("blue", 0);
			answer = ques.getType();
			//assert
			Assert::AreEqual(expected, answer);
		}

		TEST_METHOD(selectAnswerFalseToTrue)
		{
			//setup
			question ques("hello", 1);
			bool expected = true;
			bool answer;
			//act
			answer = ques.addAnswer("dog", 1);
			answer = ques.selectAnswer("dog");
			//assert
			Assert::AreEqual(expected, answer);
		}

		TEST_METHOD(trueToFalse)
		{
			//setup
			question ques("hello", 1);
			bool expected = false;
			bool answer;
			//act
			answer = ques.addAnswer("dog", 1);
			answer = ques.selectAnswer("dog");
			answer = ques.selectAnswer("dog");
			//assert
			Assert::AreEqual(expected, answer);
		}


		TEST_METHOD(selectNonExists)
		{
			//setup
			question ques("hello", 1);
			bool expected = false;
			bool answer;
			//act
			answer = ques.selectAnswer("dog");
			//assert
			Assert::AreEqual(expected, answer);
		}

		TEST_METHOD(getQuestions)
		{
			//setup
			question ques("hello", 1);
			std::vector<std::string> expected;
			expected.push_back("dog");
			expected.push_back("cat");
			//act
			ques.addAnswer("dog", 1);
			ques.addAnswer("cat", 1);

			//assert
			std::vector<std::string> answers;
			answers = ques.getAnswers();
			for (int i = 0; i < ques.getAnswers().size(); i++) {
				if (answers.at(i) != expected.at(i)) {
					Assert::Fail();
				}
			}
			Assert::AreEqual(1, 1);
		}

		TEST_METHOD(getQuestion)
		{
			//setup
			question ques("hello", 1);
			string expected = "hello";
			string answer;
			//act
			answer = ques.getQuestion();
			//assert
			Assert::AreEqual(expected, answer);
		}
		
		TEST_METHOD(getExpectedTrue)
		{
			//setup
			question ques("hello", 1);
			bool expected = true;
			bool answer;
			//act
			answer = ques.addAnswer("dog", 1);

			answer = ques.getExpected("dog");
			//assert
			Assert::AreEqual(expected, answer);
		}

		TEST_METHOD(getExpectedFalse)
		{
			//setup
			question ques("hello", 1);
			bool expected = false;
			bool answer;
			//act
			answer = ques.addAnswer("dog", 0);

			answer = ques.getExpected("dog");
			//assert
			Assert::AreEqual(expected, answer);
		}

		TEST_METHOD(getExpectedDoesntExist)
		{
			//setup
			question ques("hello", 1);
			bool expected = false;
			bool answer;
			//act
			answer = ques.addAnswer("dog", 0);

			answer = ques.getExpected("cat");
			//assert
			Assert::AreEqual(expected, answer);
		}

		TEST_METHOD(getPoints)
		{
			//setup
			question ques("hello", 3);
			int expected = 3;
			int answer;
			//act
			answer = ques.getPoints();
			//assert
			Assert::AreEqual(expected, answer);
		}
	};
}
