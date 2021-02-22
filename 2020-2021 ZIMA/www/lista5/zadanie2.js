$(document).ready(function() {
    let link = "https://cors-anywhere.herokuapp.com/" + "https://tvn24.pl/najnowsze.xml";
    $.get(link, function(tvnXML){
        let i = 0;
        $(tvnXML).find("item").each(function(){
            if(i == 5)
                return;
            let article = "";
            article += (`<li>${$(this).find("title").text()}</li>`);
            article += (`<br><ul><li>${removeIMGtvn($(this).find("description").text())}</li><br>`);
            article += (`<li><a href="${$(this).find("guid").text()}">Zobacz sam!</a></ul></li><br>`);
            $("#TVNnews").append(article);
            i++;
        })
    })
});

function removeIMGtvn(string){
    let start_newstring = string.indexOf('/>'); //wiemy ze najpierw pojawia sie zdjecie w tych znacznikach;
    return string.substring(start_newstring + 2);
}