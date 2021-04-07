function if_divisible(a, b){ //checks whether a is divisible by b
    return a % b == 0
}

function digits_sum(num){
    var sum = 0
    while(num > 0){
        sum += num % 10
        num = (num - (num % 10)) / 10
    }
    return sum;
}

function digits(num){
    var numbers = []
    while(num > 0){
        numbers.push(num % 10)
        num = (num - (num % 10)) / 10 
    }
    return numbers;
}

function program(){
    var numbers_wanted = [];
    for(let i = 1; i <= 100000; i++){
        if( if_divisible(i, digits_sum(i)) ){
            let number_ok = true
            for( number of digits(i) ){
                if( if_divisible(i, number) == false ){
                    number_ok = false
                }
            }
            if(number_ok == true){
                numbers_wanted.push(i);
                console.log(i);
            }
        }
    }
    return numbers_wanted;
}

console.log(program())
