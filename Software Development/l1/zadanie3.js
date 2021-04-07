function if_prime(a){
    if(a < 2){ return false }
    for(let i = 2; i < a; i++){
        if(a % i == 0){ 
            return false 
        }
    }
    return true
}

function primes_set(){
    var primes = [];
    for(let i = 2; i <= 100000; i++){
        if(if_prime(i)){
            primes.push(i)
        }
    }
    return primes;
}

console.log(if_prime(7))
console.log(primes_set())