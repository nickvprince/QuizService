docker run --rm --name QuizMYSQL -p 3306:3306 -e MYSQL_ROOT_PASSWORD=admin -d mysql

docker run --rm -ti -p 27501:27501 -v %cd%/Enterprise_Solution_Quizzes/QuizSharedDocker:/QuizSharedDocker quiz_webserver_dev bash