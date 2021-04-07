const http = require('http');
const express = require('express');
const multer  = require('multer');

var app = express();

app.set('views', __dirname + '/views1');
app.set('view engine', 'ejs');

app.get('/', (req, res) => {
    res.render('zad1');
})

var storage = multer.diskStorage({
    destination: function (req, file, cb) {
      cb(null, 'zad1uploads')
    },
  });

var upload = multer({ storage: storage });

app.post('/fileupload', upload.single('uploaded'), (req, res, next) => {
    const file = req.file
    if (!file) {
      console.log("Nie wybrano pliku");
    }
    res.send(file);
})

http.createServer(app).listen(3000);
console.log("I'm on!");
