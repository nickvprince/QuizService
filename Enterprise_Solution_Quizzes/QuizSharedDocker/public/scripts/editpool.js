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
    xmlHttp.open("GET", "./getPool/"+String(pool), false);
    xmlHttp.send(null);

    // Parse the services json file
    const json = xmlHttp.responseText;
    const obj = JSON.parse(json);

    console.log(obj);
    for (let x in obj) { // add questions
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





    /*
    var data = xmlHttp.responseText.toString();
    console.log(data);
    if (data[0] == "[") {
        var done = data.slice(1, data.length );
        data = " "+done;
    }
    console.log(data);

    // parse information from data || use questionPoolForm.js functions, modify to input values
    data = data.replace("[", " ");
    var question; // holds next question
    var answers =[]; // answers for question
    data = data.split('"'); // for parsing
    var arraySize = 0;// data manipulation
    var index = -1; // data manipulation

    for (var i = 0; i < data.length; i++) { // until end of input data
        if (data[i][data[i].length-1] == "r") { // remove /r from inputs
            data[i] = data[i].slice(0, data[i].length - 2);
        }
        if (index == 0) { // question
 
            question = data[i];
        }
        else { // not question
            if (data[i][0] == "," || data[i][0]==" ") {// remove un-needed seperator info from string such as [{,}]
                data[i] = data[i].slice(1, data[i].length - 1);
            }

            if (data[i].length <= 0) { // ignore data if split data is none

            }
            else { // if there is data
                if (data[i][data[i].length - 1] == "," || data[i][data[i].length - 1] == "]") {
                  
                    var tmp = data[i].split(","); // split data into all answers given for question
                    if (data[i][data[i].length - 1] == "]") { // remove other seperator info
                      
                        if (tmp[0] != tmp[tmp.length - 1][1] || tmp[1].length>1) {
                            tmp[1] = tmp[1].slice(0, tmp[1].length - 1);
                           
                        }
                       
                    }
                     
                    if (tmp.length > 2) { // if multiple answer
                      
                        var x = AddQuestion(1, String(question)); // multiple answer
                        for (var v = 0; v < answers.length; v++) {
                           
                            if (tmp[2].length > 1 || tmp[2] == "1" || tmp[2] == "0") {
                                option(x, 1, answers[v]);
                        }
                        else {
                                option(x, 0, answers[v]);
                        }
                        }
                        if (tmp[0] != tmp[tmp.length - 1][1]) {
                            for (var b = 1; b < tmp.length - 1; b++) {
                                
                                document.getElementById(String(x) + "-" + tmp[b]).checked = true;
                            }
                        }
                        else {
                            for (var b = 1; b < tmp.length; b++) {
                            
                                document.getElementById(String(x) + "-" + tmp[b][0]).checked = true;
                            }
                        
                    // check all checkboxes that are supposed to be selected
                        }
                   
                    }
                    else {
                        var x=AddQuestion(0, String(question)); // multiple choice
                        for (var v = 0; v < answers.length; v++) { // add options under question
                        
                            option(x, 0, answers[v]);
                        }
                     
                           // check radio button that was selected
                       
                        document.getElementById(String(x) + "-" + tmp[1]).setAttribute("checked", "true");
                 
                     
                    }
                    index = -1;
                    arraySize = 0;
                }
                else {
                    // add answer
                    answers[arraySize] = data[i];
                    arraySize++;
                }
            }
            
        }

        index++;
       
    }

    */
}






