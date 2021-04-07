function readWrite(){ 
    console.log("What is your name?");

    process.stdin.once('data', (inp) => {

    let name = inp.toString().trim();
    
    console.log("Hello, " + name + "!");
    process.exit();
    })
};

readWrite();