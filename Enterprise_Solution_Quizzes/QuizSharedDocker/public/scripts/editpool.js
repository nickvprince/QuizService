function load() {

    var pool;
    //get pool being edited
    
    const urlParams = new URLSearchParams(location.search);
    for (const [key, value] of urlParams) {
        pool = value;
    }
    //add the pool being edited
    document.getElementById("pname").value = pool.toString();
   
    var addTitle = document.createElement("h1");
   
    addTitle.textContent = "Editing : " + pool.toString();
    
    document.getElementById("title").insertAdjacentElement("afterbegin", addTitle);
 
   // document.getElementById("title").insertAdjacentElement("beforebegin", poolname);

    
    // http request for pool data
 
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("GET", "./getPool/"+String(pool), false);
    xmlHttp.send(null);

    // Parse the services json file
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
                    var ques = AddQuestion(1, String(x));
                } else {
                    var ques = AddQuestion(0, String(x));
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


}






