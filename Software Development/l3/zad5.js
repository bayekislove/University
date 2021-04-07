function sum(){
    let a = 0;
    for(let i = 0; i < arguments.length; i++){
        a += arguments[i];
    }
    return a;
}

console.log( sum(1, 2, 3) );
console.log( sum(1, 2, 3, 8) );