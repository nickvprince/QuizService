function loadData(poolName) {
   
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("GET", "./getPool/" + poolName.toString(), false);
    xmlHttp.send(null);
    document.getElementById("pname").setAttribute("value", poolName.toString());
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

                    var ques = AddQuestion(1, String(x), 0);
                } else {

                    var ques = AddQuestion(0, String(x), 0);
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
                      if (obj[b][n] == "true") {
                          document.getElementById(String(ques) + "-" + counter).checked = true;
                      } else {
                          document.getElementById(String(ques) + "-" + counter).checked = false;
                      }
                    counter++;

                }
            }
            countTo++;
        }
    }
    /***************************************
    ********* Question pool data end********
    ***************************************/
}

function setPoolName() {
    // Look for the corresponding GET request
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("GET", "../json/currentQuiz.json", false);
    xmlHttp.send(null);

    const obj = JSON.parse(xmlHttp.responseText);

    document.getElementById("pname").innerHTML = obj["quiz"].qp_poolid;


}