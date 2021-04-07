//sesja
var http = require('http');
var express = require('express');
var session = require('express-session');

var app = express();

app.set('view engine', 'ejs');
app.set('views', './views3');

app.use(session({
    resave: true, saveUninitialized: true, secret: 'karamba'
}));

app.use("/", (req, res) => {

    var sessionValue;
    if (!req.session.sessionValue) { //nowa wartość sesji, jeśli nie ma, to tworzymy nowa
        sessionValue = new Date().toString();
        req.session.sessionValue = sessionValue;
    } else {
        sessionValue = req.session.sessionValue; //ustawiamy wartosc sesji na obecna
    }

    res.render("index", { val: sessionValue });
});

http.createServer(app).listen(3000);