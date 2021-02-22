let marki = ['Ford', 'Fiat'];
let modele= [['Focus', 'Mondeo'],
             ['126P', '500']];

function listowanieModeli(i){
    modele[i].forEach(model => {
        let selected = document.getElementById('model');
        let opt = document.createElement('option');
        opt.appendChild(document.createTextNode(model));
        opt.value = model;
        selected.appendChild(opt);
    });
}

function listowanieMarek(){
    marki.forEach(marka => {
        let selected = document.getElementById('marka');
        let opt = document.createElement('option');
        opt.appendChild(document.createTextNode(marka));
        opt.value = marka;
        selected.appendChild(opt);
    });
}

function dodajStart(){
    listowanieMarek();
    listowanieModeli(0);
}

dodajStart();

let marka = document.getElementById('marka');
let model = document.getElementById('model');

marka.onchange = () => {
    model.options.length = 0;
    listowanieModeli(marki.indexOf(marka.value));
};

let przyciskDodaj = document.getElementById('przyciskDodaj');

przyciskDodaj.onclick = () => {
    let markaCzyModel = document.getElementsByName('rodzaj');
    console.log(markaCzyModel[0]);
    markaCzyModel.forEach(mozliwosc => {
        if(mozliwosc.checked){
            let coDodac = document.getElementById('new');
            if(mozliwosc.value == 'marka'){
                marki.push(coDodac.value);
                modele.push([]);
                marka.options.length = 0;
                listowanieMarek();
            }

            else if(mozliwosc.value == 'model'){
                modele[marki.indexOf(marka.value)].push(coDodac.value);
                model.options.length = 0;
                listowanieModeli(marki.indexOf(marka.value));
            }
            coDodac.value = '';
        }
    });
};

