let boxes = [   document.getElementById('box1'),
                document.getElementById('box2'),
                document.getElementById('box3'),
                document.getElementById('box4'),
                document.getElementById('box5')]; 

let ups = [0, 0, 0, 0, 0];

function go(i){
    if(ups[i] == 1)
        boxes[i].style.margin = '50px 30px 30px 30px';
    else{
        boxes[i].style.margin = '0px 30px 30px 30px'; }
    ups[i] = ups[i] == 1 ? 0 : 1;
}

function move(i){
    setInterval(() => { go(i) }, 1000);
    if(i != 4) setTimeout( () => { move(i + 1) }, 200);
}

move(0);