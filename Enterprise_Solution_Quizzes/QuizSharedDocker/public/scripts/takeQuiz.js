function loadTestableQuiz(){
    // Look for the corresponding GET request
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("GET", "../json/currentQuiz.json", false);
    xmlHttp.send(null);

    const obj = JSON.parse(xmlHttp.responseText);
    
    document.getElementById("takeQuizTitle").innerHTML = "Take Quiz " + obj["quiz"].id;
    document.getElementById("urltitle").innerHTML = "Take Quiz " + obj["quiz"].id;

    document.getElementById("quizTitle").innerHTML = obj["quiz"].title;

    //document.getElementById("quizDuration").value = obj["quiz"].duration;
    //document.getElementById("quizPool").value = obj["quiz"].qp_poolid;
    //document.getElementById("quizStartDate").value = obj["quiz"].startdate;
    //document.getElementById("quizEndDate").value = obj["quiz"].enddate;
}