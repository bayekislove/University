var http = require('http');
var express = require('express');
var session = require('express-session');
var FileStore = require('session-file-store')(session);

let app = express();

app.set('view engine', 'ejs');
app.set('views', './views3');

app.use(session({
    store: new FileStore,
    secret: 'keyboard cat',
    resave: true,               //domyślna ścieżka do ./sessions
    saveUninitialized: true
  })
);

app.use('/', (req, res) => {
    if (req.session.views) {
        req.session.views++;
    } else {
        req.session.views = 1;
    }
    res.render("index", { val: req.session.views });
});

http.createServer(app).listen(3000);