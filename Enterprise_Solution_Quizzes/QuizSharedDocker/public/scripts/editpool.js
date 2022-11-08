function load() {
    var pool;
    //get pool being edited
    
    const urlParams = new URLSearchParams(location.search);
    for (const [key, value] of urlParams) {
        pool = value;
    }
    //add the pool being edited
    document.getElementById("pname").value = pool.toString();
   ;
    var addTitle = document.createElement("h1");
   
    addTitle.textContent = "Editing : " + pool.toString();
    
    document.getElementById("title").insertAdjacentElement("afterbegin", addTitle);
 
   // document.getElementById("title").insertAdjacentElement("beforebegin", poolname);

    
    // http request for pool data
 
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("GET", "/getPool/" + pool.toString(), false);
    xmlHttp.send(null);
    // if file doesnt exist or fails to load go back to selectpool after alerting the user
    if (xmlHttp.responseText.toString() == "fail") {
        alert("Error : Failed to find question pool");
        window.location.replace('/selectPool.html?type=edit');
    }
    var data = xmlHttp.responseText.toString();

    // parse information from data || use questionPoolForm.js functions, modify to input values
    data = data.replace("[", " ");
    var question;
    var answers =[];
    data = data.split('"');
    var arraySize = 0;
    var index = -1;
    for (var i = 0; i < data.length; i++) {
        if (data[i][data[i].length-1] == "r") {
            data[i] = data[i].slice(0, data[i].length - 2);
        }
        if (index == 0) {
            alert("Question : " + data[i]);
            question = data[i];
        }
        else {
            if (data[i][0] == "," || data[i][0]==" ") {
                data[i] = data[i].slice(1, data[i].length - 1);
            }

            if (data[i].length <= 0) {

            }
            else {
                if (data[i][data[i].length - 1] == "," || data[i][data[i].length - 1] == "]") {
                    var tmp = data[i].split(",");
                    if (data[i][data[i].length - 1] == "]") {
                        tmp[1] = tmp[1].slice(0, tmp[1].length - 1);
                    }
                    if (tmp.length > 2) {
                        var x = AddQuestion(1, String(question)); // multiple answer
                        for (var v = 0; v < answers.length; v++) {
                            option(x, 1, answers[v]);
                        }
                        for (var b = 1; b < tmp.length - 1; b++) {
                            alert("selected: " + tmp[b]);
                        }
                    }
                    else {
                        var x=AddQuestion(0, String(question)); // multiple choice
                        for (var v = 0; v < answers.length; v++) {
                            option(x, 0, answers[v]);
                        }
                        alert("selected: " + tmp[1]);
                    }
                    index = -1;
                    arraySize = 0;
                }
                else {
                    alert("Answer : " + data[i]);
                    answers[arraySize] = data[i];
                    arraySize++;
                }
            }
            
        }

        index++;
       
    }

    
}






