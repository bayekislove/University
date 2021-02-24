const http = require('http');
const express = require('express');

app = express();

app.set('view engine', 'ejs');
app.set('views', __dirname + '/views2');

app.use('/', (req, res) => {
    res.render('outted.ejs');
})

http.createServer(app).listen(3000);
console.log('I"m on!');