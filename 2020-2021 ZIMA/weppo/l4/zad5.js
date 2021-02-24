const fs = require('fs');

fs.readFile('./z5txt.txt', 'utf8' , (err, data) => {
    if (err) {
      console.error(err)
      return
    }
    console.log(data)
  })