function forEach(a, f){
    for(let i = 0; i < a.length; i++){
        f(a[i]);
    }
}

a = [1, 3];
forEach(a, ( _ ) => { return _ + 1;});
function fe(n){ console.log( n ); };

forEach(a, fe);

function map(a, f){
    for(let i = 0; i < a.length; i++){
        a[i] = f(a[i]);
    }
}

function filter(a, f){
    pom = [];
    for(let i = 0; i < a.length; i++){
        if(f(a[i]))
            pom.push(a[i]);
    }
    return pom;
}

a = [1,2,3,4];
var fil_pom = function (n){
    return n < 3;
}

console.log(filter( a, _ => _ < 3 ));
console.log(filter( a, fil_pom));

map( a, _ => _ * 2 );
console.log(a);
function asda(n){
    return n * 2;
}
map( a, asda);
console.log(a);
