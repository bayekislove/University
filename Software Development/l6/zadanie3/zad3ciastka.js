//ciastka
const http = require('http');
const express = require('express');
const cookieParser = require('cookie-parser');

app = express();

app.set('view engine', 'ejs');
app.set('views', __dirname + '/views3');

app.use(cookieParser("karamba"));

app.use(express.urlencoded({
    extended: true
}));

app.use("/", (req, res) => {
    var cookieVal;
    if (!req.signedCookies.cookie) { //dodajemy ciastko, jesli go nei ma 
        cookieVal = new Date().toString();
        res.cookie('cookie', cookieVal, { signed: true });
    } else { //ciastko juz jest, wiec przekazujemy jego wartosc do odczytania
        cookieVal = req.signedCookies.cookie;
    }
    res.render("index", { val: cookieVal }); //odczytanie ciastka
});

http.createServer(app).listen(3000);
console.log('I"m on!');