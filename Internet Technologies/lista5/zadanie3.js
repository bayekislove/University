$(document).ready(function(){
    $.getJSON("zadanie3.json", function(data){
        let news = data.rss.channel.item;
        let musTempTitle = '<li>{{title}}</li>';
        let musTempDesc = '<ul><li>{{description.__cdata}}</li>';
        let musTempLink = '<li><a href="{{link}}">Zobacz sam!</a></ul></li>';
        let musTemp = musTempTitle + musTempDesc + musTempLink;

        for(let _ = 0; _ < 5; _++){
            let descPom = news[_].description.__cdata;
            news[_].description.__cdata = removeIMGtvn(descPom);
            let endText = Mustache.render(musTemp, news[_]);
            $("#TVNnews").append(endText);
        }
    })
})

function removeIMGtvn(string){
    let start_newstring = string.indexOf('/>'); //wiemy ze najpierw pojawia sie zdjecie w tych znacznikach;
    return string.substring(start_newstring + 2);
}