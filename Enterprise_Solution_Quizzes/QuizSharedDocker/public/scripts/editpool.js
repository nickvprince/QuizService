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
   
    data = data.split('"');
    var index = -1;
    for (var i = 0; i < data.length; i++) {
        if (data[i][data[i].length-1] == "r") {
            data[i] = data[i].slice(0, data[i].length - 2);
        }
        if (index == 0) {
            alert("Question : " + data[i]);

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
                        for (var b = 1; b < tmp.length - 1; b++) {
                            alert("selected: " + tmp[b]);
                        }
                    }
                    else {
                        alert("selected: " + tmp[1]);
                    }
                    index = -1;
                }
                else {
                    alert("Answer : " + data[i]);
                }
            }
            
        }

        index++;
       
    }

    
}




