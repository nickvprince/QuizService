var formID = 0;
var buttonID = 0;
var optionID = 0;

function start() { // on startup if query string it created then alert the user a pool was created
    const urlParams = new URLSearchParams(location.search);
    for (const [key, value] of urlParams) {
        if (key == "created" && value == "true") {
            alert("Question Pool Created");
        }
        else if (key == "created" && value == "false") { // if query is false then alert user pool failed to create
            alert("Question Pool not Created");
        }
    }
}

function Enter() { // submit question pool to be saved
    var query = "?"
    var fromEdit = false;
    const urlParams = new URLSearchParams(location.search); // if from edit pool act differently
    for (const [key, value] of urlParams) {
        if (key == "pool") {
            query += "type=edit&&";
            fromEdit = true;
        }
    }
  
    query += "pool=" +document.getElementById("pname").value + "&&";
    var ids = document.querySelectorAll('[id]');
    
    Array.prototype.forEach.call(ids, function (el, i) { // add all questions as an array
        // "el" is your element
        if (el.id.toString().includes("Q")) {
            query += "Questions[]=";
            var f = document.getElementById(el.id).value
            query += f;
            query += "&";

        }
    });
    query += "&";

    var checked = false;
    var tmp = 0;
    Array.prototype.forEach.call(ids, function (el, i) { // add all options for each question
      
       
        if (el.id.toString().includes(":")) {
          
            var f = document.getElementById(el.id).value
            var d = el.id.toString().split(':');
            if (checked == false) {
                tmp = d[0];
                checked = true;
            }
            if (d[0] == tmp) {
                query += ("Q" + d[0] + "A[]="); //Q0A for question 0 array Q1A for question 1 array and so on
                query += f;
                query += "&";
            }
            else {
                query += ("&Q" + d[0] + "A[]=");
                query += f;
                query += "&";
                tmp--;
            }
        }
    });
    query += "&";
    checked = false;
    tmp = 0;
    var count = 0;
    Array.prototype.forEach.call(ids, function (el, i) { // add all selected answer values to an array
     
        if (el.id.toString().includes("-")) {
           
            var f = document.getElementById(el.id).checked
            if (f == true) {
               
                var d = el.id.toString().split('-');
                var string = el.id.toString().replace('-',':');
              
                var n = document.getElementById(string.toString()).value;
               
                query += "Checked" + d[0].toString()+"[]=";
                query += n;
                query += "&";
            }
        }
    });
    query += "&";
    var tmp = query.slice(0, -2);
    var currentHost = window.location.host; // direct to new page with all data in query string
    alert(tmp);
        window.location.replace('/savepool' + tmp);
    
}


function nextID(b) { // get the next available ID

    var x = 0;
    var ids = document.querySelectorAll('[id]');
    Array.prototype.forEach.call(ids, function (el, i) {
        if (el.id.toString().includes(b.toString())) {
            x++;
        }
       
    });
    return x;
}
function alter(ID) {
    console.log("Change : " + ID);
    var ids = document.querySelectorAll('[id]');

    Array.prototype.forEach.call(ids, function (el, i) { // add all questions as an array
        // "el" is your element
        if (el.id.toString().includes(ID + "-")) {
            if (document.getElementById(el.id).getAttribute("type").toString() == "radio") {
                document.getElementById(el.id).setAttribute("type", "checkbox")
            } else {
                document.getElementById(el.id).setAttribute("type", "radio")
            }
        }
    });

}
function removeQuestion(buttonID) {
    console.log("Remove : " + buttonID);
    document.getElementById(buttonID).remove();
    var ids = document.querySelectorAll('[id]');

    Array.prototype.forEach.call(ids, function (el, i) { // add all questions as an array
        // "el" is your element
        if (el.id.toString().includes(buttonID + "-") || el.id.toString().includes(buttonID + ":")) {
            document.getElementById(el.id).remove();
        }
    });
}

function AddQuestion(i, k) {
    var t = String(i);
    var b = document.createElement('input');
    var d = document.createElement('input'); // create a button and textfield for a question, button allows you to add options
    var z = document.createElement('br');


    // delete button
    var deleteQuestionButton = document.createElement('input');
    deleteQuestionButton.setAttribute("type", "button");
    deleteQuestionButton.setAttribute("id", buttonID);
    deleteQuestionButton.setAttribute("value", "Remove Question");
    deleteQuestionButton.setAttribute("onclick", "removeQuestion(" + buttonID +")"); // set button function to use params of this button id and if its multiple answer or multiple choice.

    //switch between multiple answer and multiple choice
    var switchbtn= document.createElement('input');
    switchbtn.setAttribute("type", "button");
    switchbtn.setAttribute("id", buttonID);
    switchbtn.setAttribute("value", "Change Type");
    switchbtn.setAttribute("onclick", "alter(" + buttonID + ")"); // set button function to use params of this button id and if its multiple answer or multiple choice.




    d.setAttribute("type", "text");
    d.setAttribute("value", String(k));
    d.setAttribute("id", "Q" + formID);
    b.setAttribute("type", "button");
    b.setAttribute("id", buttonID);
    b.setAttribute("value", "add option");
    b.setAttribute("onclick", "option(" + buttonID + "," + t + ", 'Answer')"); // set button function to use params of this button id and if its multiple answer or multiple choice.
    buttonID++;
    var i = document.createElement('form');
    i.setAttribute("id", formID);
    formID++;
    i.appendChild(d);
    i.appendChild(b);
    i.appendChild(deleteQuestionButton);
    i.appendChild(switchbtn);

   
    document.getElementById("insertHere").insertAdjacentElement("afterend", i);
    document.getElementById("insertHere").insertAdjacentElement("afterend", z); // add elements
 
   // document.getElementById((formID) + "Q").insertAdjacentElement("beforebegin", z);
    return buttonID - 1;
}



function option(i, c, name) { // add option to a question
 
    var n = document.createElement('br');
    var b = String(i);
    var i = document.createElement('input');
    var z = document.createElement('input'); // add a textfield and either a radio button or check box
    i.setAttribute("id", b + "-" + nextID(b + "-").toString());
    i.setAttribute("name", b);
    z.setAttribute("type", "text");
    z.setAttribute("value", String(name));
    z.setAttribute("id", b + ":" + nextID(b + ":").toString());
    optionID++;
    if (c == 0) { // add radio button
        i.setAttribute("type", "radio")

        document.getElementById(b).insertAdjacentElement("afterend", i);
        document.getElementById(b).insertAdjacentElement("afterend", z);
        document.getElementById(b).insertAdjacentElement("afterend", n);
    }
    else if (c == 1) { // add checkbox
        i.setAttribute("type", "checkbox")
        document.getElementById(b).insertAdjacentElement("afterend", i);
        document.getElementById(b).insertAdjacentElement("afterend", z);
        document.getElementById(b).insertAdjacentElement("afterend", n);
    }
    else {
        alert("Unexpected input");
    }

}