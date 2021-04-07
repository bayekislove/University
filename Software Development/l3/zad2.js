function fib(n){
    if(n > 1) 
        return fib(n - 1) + fib(n - 2);
    return 1;
}

var start = new Date().getTime();
console.log(fib(20));
console.log(new Date().getTime() - start);

function memo(f){

    var cache = {}
    return (n) => {
        if( cache[n] == undefined){
            let pom = f(n);
            cache[n] = pom;
            return pom;
        }
        else{
            return cache[n];
        }
    }
}

var fib_better = memo(fib);

start = new Date().getTime();
console.log(fib_better(50));
console.log(fib_better(49));
console.log(new Date().getTime() - start);

var fib = memo(fib);

start = new Date().getTime();
console.log(fib(50));
console.log(fib(49));
console.log(new Date().getTime() - start);
