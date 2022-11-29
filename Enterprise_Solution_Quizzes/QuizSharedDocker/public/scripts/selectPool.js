
function load() {



    const urlParams = new URLSearchParams(location.search);
    var b = document.createElement('input');
    b.setAttribute("type", "button");
    b.setAttribute("class", "main_btn");
    b.setAttribute("role", "button");
    b.setAttribute("id", "Submit"); // create a button to add
    
    for (const [key, value] of urlParams) {
        if (key == "type" && value == "edit") { // if came from edit area set button to say edit 
            b.setAttribute("value", "Edit");
          
            b.setAttribute("onclick", "out(0)");
        }
        else if (key == "type" && value == "delete") { // if supposed to delete set button so say delete
            b.setAttribute("value", "Delete");
            b.setAttribute("onclick", "out(1)");
            
        }
    }
       
    document.getElementById("insertHere").insertAdjacentElement("afterend", b);

     
        
}
function out(i) { // got to edit pool or delete pool based on i, with the pool name provided
    
    var selectedpool =document.getElementById("quizPool").value;
    if (i == 0) {
        window.location.replace("editPool.html?pool=" + selectedpool.toString());
    }
    else if (i == 1) {
        var xmlHttp = new XMLHttpRequest();
        xmlHttp.open("POST", "deletePool/" + selectedpool.toString(), false);
        xmlHttp.send();

        var xmlHttp2 = new XMLHttpRequest();
        xmlHttp2.open("GET", "/succeeded", false);
        xmlHttp2.send();
        alert(xmlHttp2.response);
        window.location.replace("index.html");
    }
}