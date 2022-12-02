
function loadTestableQuiz() {
    // Look for the corresponding GET request
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("GET", "../json/currentQuiz.json", false);
    xmlHttp.send(null);

    const obj1 = JSON.parse(xmlHttp.responseText);
    
    document.getElementById("takeTitle").innerHTML = "Take Quiz " + obj1["quiz"].id;
    document.getElementById("urltitle").innerHTML = "Take Quiz " + obj1["quiz"].id;

    document.getElementById("Title").innerHTML = obj1["quiz"].title;
    
   
    
 
    var poolName = obj1["quiz"].qp_poolid;
    /***************************************
     ********* Question pool data start ****
     ***************************************/
    document.getElementById("pname").setAttribute("value",poolName.toString());
    var brk = document.createElement('br');
    var brk2 = document.createElement('br');

    document.getElementById("insertHere").insertAdjacentElement("afterend", brk); // insert breaks for space between submit
    document.getElementById("insertHere").insertAdjacentElement("afterend", brk2);

    //insert elements here for questionPool
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("GET", "./getPool/" + poolName.toString(), false);
    xmlHttp.send(null);
    
    // Parse the pool json file
    const json = xmlHttp.responseText;

    const obj = JSON.parse(json);
    var counter = 0;
    for (let x in obj) {
        counter++;
    }
    console.log(counter)

    for (var i = counter; i > -1; i--) {
        var countTo = 0;
        for (let x in obj) { // add questions
            if (countTo == i) {
                console.log(x);

                var b = x.toString();
                var counter = 0;
                var type = 0;

                for (let k in obj[b]) { // get number of correct answers
                    // console.log(obj[b][k]);
                    if (obj[b][k] == "true") {
                        type++;
                    }
                }
                if (type > 1) { // if multiple choice or multiple answer
                  
                    var ques = AddQuestion(1, String(x),0);
                } else {
                 
                    var ques = AddQuestion(0, String(x),0);
                }
                type = 0;

                for (let n in obj[b]) { // add options

                    console.log("Option : ");
                    for (let k in obj[b]) {
                        // console.log(obj[b][k]);
                        if (obj[b][k] == "true") {
                            type++;
                        }
                    }
                    if (type > 1) {
                        option(ques, 1, String(n));
                    } else {
                        option(ques, 0, String(n));
                    }
                    type = 0;
                  /*  if (obj[b][n] == "true") {
                        document.getElementById(String(ques) + "-" + counter).checked = true;
                    } else {
                        document.getElementById(String(ques) + "-" + counter).checked = false;
                    }*/
                    counter++;

                }
            }
            countTo++;
        }
    }
    /***************************************
    ********* Question pool data end********
    ***************************************/

    //document.getElementById("quizDuration").value = obj["quiz"].duration;
    //document.getElementById("quizPool").value = obj["quiz"].qp_poolid;
    //document.getElementById("quizStartDate").value = obj["quiz"].startdate;
    //document.getElementById("quizEndDate").value = obj["quiz"].enddate;
}
function startTimer() {

    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("GET", "../json/currentQuiz.json", false);
    xmlHttp.send(null);

    const obj1 = JSON.parse(xmlHttp.responseText);
    var duration = obj1["quiz"].duration;
    var today = new Date();
    var toadd = today.getMinutes();
  
    today.setMinutes(parseInt(duration) + parseInt(toadd));
   
// Set the date we're counting down to
        var countDownDate = new Date(today).getTime();

        // Update the count down every 1 second
        var x = setInterval(function() {

  // Get today's date and time
  var now = new Date().getTime();

        // Find the distance between now and the count down date
        var distance = countDownDate - now;

        // Time calculations for days, hours, minutes and seconds
        var days = Math.floor(distance / (1000 * 60 * 60 * 24));
        var hours = Math.floor((distance % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60));
        var minutes = Math.floor((distance % (1000 * 60 * 60)) / (1000 * 60));
        var seconds = Math.floor((distance % (1000 * 60)) / 1000);

        // Output the result in an element with id="demo"
        document.getElementById("demo").innerHTML = days + "d " + hours + "h "
        + minutes + "m " + seconds + "s ";

        // If the count down is over, write some text 
        if (distance < 0) {
            clearInterval(x);
            Enter();
  }
}, 500);


}
