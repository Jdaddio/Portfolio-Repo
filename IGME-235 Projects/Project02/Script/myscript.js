//STOP SHOWING "EPISODE COUNT" FOR MANGA


const prefix = "jpd5286-";
const nameKey = prefix + "name";
const mediaKey = prefix + "media";
const genreKey = prefix + "genre";

let searchResults;
let searchMedia;
let pageNumber = 1;
let prevPageNumber = 1;

window.onload = (e) => {
    if (localStorage.getItem(mediaKey)){document.querySelector("#mediaSelect").value = localStorage.getItem(mediaKey);}
    document.querySelector("#nameInput").value = localStorage.getItem(nameKey);
    document.querySelector("#genreInput").value = localStorage.getItem(genreKey);
    let list = genreInput.getAttribute('list');
    let genres = document.querySelectorAll('#' + list + ' option');
    for (let i = 0; i < genres.length; i++){
        if (genres[i].getAttribute('data-value') == document.querySelector("#genreInput").value){
            document.querySelector("#genreInput").value = genres[i].innerHTML;
            if (genres[i].innerHTML == "None"){
                document.querySelector("#genreInput").value = "";
            }
            else{
                document.querySelector("#genreInputLabel").innerHTML = "Genre: " + genres[i].innerHTML;
            }
            break;
        }
    }
    document.querySelector("#genreInput-hidden").value = localStorage.getItem(genreKey);

    document.querySelector("#search").onclick = searchButtonClicked;
    document.querySelector("#mediaSelect").onchange = mediaSelectChanged;
    document.querySelector("#genreInput").onchange = genreInputChanged;
    searchMedia = document.querySelector("#mediaSelect").value;
}
	
let displayTerm = "";

function searchButtonClicked(reset){
    if (reset){
        pageNumber = 1;
        prevPageNumber = 1;
    }
    infoClosed();
    document.querySelector("#content").innerHTML = `<img id='loading' src = 'Images/loading.gif' alt = 'Loading' />`;
    let url = "https://api.jikan.moe/v3/search";
    let media = document.querySelector("#mediaSelect").value;
    localStorage.setItem(mediaKey, media);
    searchMedia = document.querySelector("#mediaSelect").value;
    url += "/" + media + `?q=`;
    let name = document.querySelector("#nameInput").value;
    name = encodeURIComponent(name.trim());
    localStorage.setItem(nameKey, document.querySelector("#nameInput").value);
    if (name.length >= 3){
        url += name + `&page=${pageNumber.toString()}`;
    }
    else{
        url += `&order_by=members&sort=desc&page=${pageNumber.toString()}`;
    }
    let genre = document.querySelector("#genreInput-hidden").value;
    localStorage.setItem(genreKey, genre);
    if (genre.length > 0){
        url += "&genre=" + genre;
    }
    console.log(url);

    getData(url);
}

function getData(url){

    let xhr = new XMLHttpRequest();

    xhr.onload = dataLoaded;

    xhr.onerror = dataError;
    
    xhr.open("GET",url);
    xhr.send();
}

function dataLoaded(e){
    let xhr = e.target;
    console.log(xhr.responseText);
    let obj = JSON.parse(xhr.responseText);
    if (!obj.results || obj.results.length == 0){
        document.querySelector("#loading").remove();
        alert("No response from API or no results found");
        console.log("API issue or no more content to load");
        pageNumber = prevPageNumber;
        console.log(pageNumber.toString());
        if (document.querySelectorAll(".prevButton") != null && document.querySelectorAll(".pageNumInput") != null){
            for (let previous of document.querySelectorAll(".prevButton")){
                if (pageNumber == 1){
                    previous.disabled = true;
                }
            }
            for (let numberInput of document.querySelectorAll(".pageNumInput")){
                numberInput.placeholder = pageNumber;
                numberInput.value = "";
            }
        }
        searchButtonClicked(false);
        return;
    }
    document.querySelector("#loading").remove();
    let results = obj.results;
    searchResults = obj.results;
    console.log("results.length = " + results.length);
    document.querySelector("#contentHeader").innerHTML = "<h2>Results:</h2>";
    document.querySelector("#contentHeader").innerHTML += `<button type="button" class="prevButton">Previous Page</button>`; 
    document.querySelector("#contentHeader").innerHTML += `<input type="text" class="pageNumInput" placeholder="${pageNumber.toString()}"/>`; 
    document.querySelector("#contentHeader").innerHTML += `<button type="button" class="nextButton">Next Page</button>`;
    let bigString = "";
    for (let i = 0; i < results.length; i++){
        let result = results[i];
        let smallURL = result.image_url;
        let name = result.title;
        let line = `<div class = 'result'><button class = "ResultButton" type="button"> <img src = '${smallURL}' title = '${result.id}' />`;
        line += `<p><b>${name}</b></p>`;
        line += `</button></div>`;
        bigString += line;
    }
    document.querySelector("#content").innerHTML = bigString;
    //document.querySelector("#status").innerHTML = "<b>Success!</b><p><i>Here are " + results.length + " results'</i></p>";
    let resultButtons = document.querySelectorAll(".ResultButton");
    for (let i = 0; i < resultButtons.length; i++){ //for every button in the array of buttons, 
        resultButtons[i].onclick = function(e){ //a function is added to the button's onclick event that displays information in the "content2" div
            location.href = "#content";
            window.scrollBy(0,-100);
            let string = `<button type="button" id="closeInfo">Close</button>`;
            string += `<p><b>${searchResults[i].title}</b></p>`;
            if (searchMedia == "anime") string += `<p>Rated <i>"${searchResults[i].rated}"</i></p>`;
            string += `<img src = '${searchResults[i].image_url}' title = '${searchResults[i].id}' />`;
            if (searchMedia == "anime") string += `<p>Episode count: ${searchResults[i].episodes}</p>`;
            if (searchMedia == "manga") {
                string += `<p>Volume count: ${searchResults[i].volumes}</p>`;
                string += `<p>Chapter count: ${searchResults[i].chapters}</p>`;
            }
            string += `<p>Synopsis: <i>"${searchResults[i].synopsis}"</i></p>`;
            string += `<p>Rating: ${searchResults[i].score}</p>`;
            string += `<p>See on myanimelist.net: <a target = '_blank' href = '${searchResults[i].url}'>${searchResults[i].url}</a></p>`;
            string += `<button type="button" id="moreAnime">See more like this</button>`;
            document.querySelector("#content2").innerHTML = string;
            document.querySelector("#content").style.width = "45%";
            document.querySelector("#content2").style.width = "45%";
            //document.querySelector("#content2").style.position = "fixed";
            document.querySelector("#closeInfo").onclick = infoClosed;

            let url = "https://api.jikan.moe/v3/";
            url += searchMedia;
            url += "/" + searchResults[i].mal_id + "/recommendations";
            console.log(url);
            document.querySelector("#moreAnime").onclick = function(e){
                document.querySelector("#moreAnime").remove();
                document.querySelector("#content2").innerHTML += `<p>More Anime like this:</p>`;
                document.querySelector("#content2").innerHTML += `<img id='loading' src = 'Images/loading.gif' alt = 'Loading' />`;
                getMoreData(url);
            }
        }
    }
    document.querySelector("#contentFooter").innerHTML = "";
    document.querySelector("#contentFooter").innerHTML += `<button type="button" class="prevButton">Previous Page</button>`; 
    document.querySelector("#contentFooter").innerHTML += `<input type="text" class="pageNumInput" placeholder="${pageNumber.toString()}"/>`; 
    document.querySelector("#contentFooter").innerHTML += `<button type="button" class="nextButton">Next Page</button>`;
    for (let previous of document.querySelectorAll(".prevButton")){
        if (pageNumber == 1){
            previous.disabled = true;
        }
        else{
            previous.onclick = function(e){ prevPageNumber = pageNumber; pageNumber -= 1; searchButtonClicked(false); }
        }
    }
    for (let next of document.querySelectorAll(".nextButton")){
        next.onclick = function(e){ prevPageNumber = pageNumber; pageNumber += 1; searchButtonClicked(false); }
    }
    for (let numberInput of document.querySelectorAll(".pageNumInput")){
        numberInput.addEventListener("keyup", function(e){ if(e.keyCode == 13){if (numberInput.value >= 1){prevPageNumber = pageNumber; pageNumber = parseInt(numberInput.value); searchButtonClicked(false);}else{alert(`${numberInput.value} is not a valid number`);} } })
        //numberInput.addEventListener("blur", function(e){ if (numberInput.value >= 1){prevPageNumber = pageNumber; pageNumber = parseInt(numberInput.value); searchButtonClicked(false);}else{alert(`${numberInput.value} is not a valid number`);} })
    }
}

function dataError(e){
    alert("An error occured");
    console.log("An error occured");
}

function mediaSelectChanged(){
    if (document.querySelector("#mediaSelect").value == "anime"){
        document.querySelector("#genres").innerHTML = 
        "<option data-value=''>None</option>" +
        "<option data-value='1'>Action</option>" +
        "<option data-value='2'>Adventure</option>" +
        "<option data-value='3'>Cars</option>" +
        "<option data-value='4'>Comedy</option>" +
        "<option data-value='5'>Avante Garde</option>" +
        "<option data-value='6'>Demons</option>" +
        "<option data-value='7'>Mystery</option>" +
        "<option data-value='8'>Drama</option>" +
        "<option data-value='9'>Ecchi</option>" +
        "<option data-value='10'>Fantasy</option>" +
        "<option data-value='11'>Game</option>" +
        "<option data-value='13'>Historical</option>" +
        "<option data-value='14'>Horror</option>" +
        "<option data-value='15'>Kids</option>" +
        "<option data-value='17'>Martial Arts</option>" +
        "<option data-value='18'>Mecha</option>" +
        "<option data-value='19'>Music</option>" +
        "<option data-value='20'>Parody</option>" +
        "<option data-value='21'>Samurai</option>" +
        "<option data-value='22'>Romance</option>" +
        "<option data-value='23'>School</option>" +
        "<option data-value='24'>Sci-Fi</option>" +
        "<option data-value='25'>Shoujo</option>" +
        "<option data-value='27'>Shounen</option>" +
        "<option data-value='29'>Space</option>" +
        "<option data-value='30'>Sports</option>" +
        "<option data-value='31'>Super Power</option>" + 
        "<option data-value='32'>Vampire</option>" + 
        "<option data-value='36'>Slice of Life</option>" +
        "<option data-value='37'>Supernatural</option>" +
        "<option data-value='38'>Military</option>" +
        "<option data-value='39'>Police</option>" +
        "<option data-value='40'>Psychological</option>" +
        "<option data-value='41'>Suspense</option>"+ 
        "<option data-value='42'>Seinen</option>" + 
        "<option data-value='43'>Josei</option>"+ 
        "<option data-value='46'>Award Winning</option>" +
        "<option data-value='47'>Gourmet</option>" +
        "<option data-value='48'>Work Life</option>";
    }
    if (document.querySelector("#mediaSelect").value == "manga"){
        document.querySelector("#genres").innerHTML = 
        "<option data-value=''>None</option>" +
        "<option data-value='1'>Action</option>" +
        "<option data-value='2'>Adventure</option>" +
        "<option data-value='3'>Cars</option>" +
        "<option data-value='4'>Comedy</option>" +
        "<option data-value='5'>Avante Garde</option>" +
        "<option data-value='6'>Demons</option>" +
        "<option data-value='7'>Mystery</option>" +
        "<option data-value='8'>Drama</option>" +
        "<option data-value='9'>Ecchi</option>" +
        "<option data-value='10'>Fantasy</option>" +
        "<option data-value='11'>Game</option>" +
        "<option data-value='13'>Historical</option>" +
        "<option data-value='14'>Horror</option>" +
        "<option data-value='15'>Kids</option>" +
        "<option data-value='17'>Martial Arts</option>" +
        "<option data-value='18'>Mecha</option>" +
        "<option data-value='19'>Music</option>" +
        "<option data-value='20'>Parody</option>" +
        "<option data-value='21'>Samurai</option>" +
        "<option data-value='22'>Romance</option>" +
        "<option data-value='23'>School</option>" +
        "<option data-value='24'>Sci-Fi</option>" +
        "<option data-value='25'>Shoujo</option>" +
        "<option data-value='27'>Shounen</option>" +
        "<option data-value='29'>Space</option>" +
        "<option data-value='30'>Sports</option>" +
        "<option data-value='31'>Super Power</option>" + 
        "<option data-value='32'>Vampire</option>" + 
        "<option data-value='36'>Slice of Life</option>" +
        "<option data-value='37'>Supernatural</option>" +
        "<option data-value='38'>Military</option>" +
        "<option data-value='39'>Police</option>" +
        "<option data-value='40'>Psychological</option>" +
        "<option data-value='41'>Seinen</option>" + 
        "<option data-value='42'>Josei</option>"+ 
        "<option data-value='45'>Suspense</option>" +
        "<option data-value='46'>Award Winning</option>" +
        "<option data-value='47'>Gourmet</option>" +
        "<option data-value='48'>Work Life</option>";
    }
    localStorage.setItem(mediaKey, document.querySelector("#mediaSelect").value);
    searchMedia = document.querySelector("#mediaSelect").value;
}

function genreInputChanged(){
    let genreInput = document.querySelector("#genreInput");
    let hiddenGenreInput = document.querySelector("#genreInput-hidden");

    let list = genreInput.getAttribute('list');
    let genres = document.querySelectorAll('#' + list + ' option');
    for (let i = 0; i < genres.length; i++){
        if (genres[i].innerHTML == genreInput.value){
            hiddenGenreInput.value = genres[i].getAttribute('data-value');
            //console.log(genres[i].getAttribute('data-value'));
            if (genres[i].innerHTML == "None"){
                document.querySelector("#genreInputLabel").innerHTML = "Genre: ";
            }
            else{
                document.querySelector("#genreInputLabel").innerHTML = "Genre: " + genres[i].innerHTML;
            }
            break;
        }
    }
    localStorage.setItem(genreKey, document.querySelector("#genreInput").value);
}

function infoClosed(){
    //document.querySelector("#closeInfo").onclick = null;
    document.querySelector("#content2").innerHTML = "";
    document.querySelector("#content2").style.width = "0%";
    document.querySelector("#content").style.width = "90%";
}

function getMoreData(url){

    let xhr = new XMLHttpRequest();

    xhr.onload = moreDataLoaded;

    xhr.onerror = dataError;
    
    xhr.open("GET",url);
    xhr.send();
}

function moreDataLoaded(e){
    let xhr = e.target;
    console.log(xhr.responseText);
    let obj = JSON.parse(xhr.responseText);
    if (!obj.recommendations || obj.recommendations.length == 0){
        document.querySelector("#loading").remove();
        alert("No response from API or no results found");
        console.log("API issue or no more content to load");
        return;
    }
    document.querySelector("#loading").remove();
    let results = obj.recommendations;
    console.log("results.length = " + results.length);
    let bigString = `<div id="moreResults">`;
    for (let i = 0; i < results.length; i++){
        let result = results[i];
        let smallURL = result.image_url;
        let name = result.title;
        
        let line = `<div class="newResult"><img src = '${smallURL}' title = '${result.id}' height = "210px"/>`;

        line += `<div class="resultText"><p>${name} <br> <a target = '_blank' href = '${result.url}'>See on myanimelist.net</a> </p></div>`;

        line += `</div>`;

        bigString += line;
    }
    bigString += `</div>`;
    document.querySelector("#content2").innerHTML += bigString;
    document.querySelector("#moreResults").style.maxHeight = "50vw";    
    document.querySelector("#closeInfo").onclick = infoClosed;
}