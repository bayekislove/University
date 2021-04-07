let adverbs = ["appropriately", "assertively", "authoritatively", "collaboratively"];
let verbs = ["actualize", "recaptiualize", "reconceptualize", "redefine", "re-engineer", "reintermediate", "reinvent"];
let adjectives = ["unique", "user-centric", "user friendly", "value-added", "vertical"];
let nouns = ["methods of empowerment", "metrics", "mindshare", "models", "networks", "niches", "niche markets", "nosql"];

function getRandomInt(min, max) {
    min = Math.ceil(min);
    max = Math.floor(max);
    return Math.floor(Math.random() * (max - min)) + min;
}

function IndexInArray(k, T) {
    if(k > T.length - 1)
        return ''
    return T[k]
}

$(document).ready(function () {
    for (let i = 0; i < Math.max(adverbs.length, verbs.length, adjectives.length, nouns.length); i++) {
        $('#bullshitTab').find('tbody:last').append('<tr><td>' + IndexInArray(i, adverbs) + '</td><td>' + IndexInArray(i, verbs)
            + '</td><td>' + IndexInArray(i, adjectives) + '</td><td>' + IndexInArray(i, nouns) + '</td></tr>');
    }

    $('#generate').on('click', function () {
        $('#generatedBullshit').val(
            adverbs[getRandomInt(0, adverbs.length)] + ' ' +
            verbs[getRandomInt(0, verbs.length)] + ' ' +
            adjectives[getRandomInt(0, adjectives.length)] + ' ' +
            nouns[getRandomInt(0, nouns.length)])
    })
})