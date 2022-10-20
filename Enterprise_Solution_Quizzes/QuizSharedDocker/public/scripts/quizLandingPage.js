function buttonclick(id){
    switch(id){
        case "home": {
            location.href = "../index.html";
            break;
        }
        case "create-quiz-button": {
            location.href = "../createQuiz.html";
            break;
        }
        case "edit-quiz-button": {
            location.href = "../editQuiz.html";
            break;
        }
        case "delete-quiz-button": {
            location.href = "../deleteQuiz.html";
            break;
        }
        default:
            break;
    }
}