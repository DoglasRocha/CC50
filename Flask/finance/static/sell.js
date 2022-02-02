const alert_things = (textInStock, textInShares) => {

    if (!textInStock && !textInShares)
    {
        warning.textContent = 'You must provide a stock symbol and a shares number!';
    }
    else if (!textInStock)
    {
        warning.textContent = 'You must provide a stock symbol!';
    }
    else if (!textInShares)
    {
        warning.textContent = 'You must provide a shares number!';
    }
    else
    {
        warning.textContent = '';
    }
} 


let stock = document.querySelector('#stock');
let shares = document.querySelector('#shares');
let warning = document.querySelector('#warning');

let stockText;
let sharesNumber;
let stockHasText = false;
let sharesHasText = false;

if (stock.value.length > 0)
{
    stockHasText = true;
    stock.value = stock.value.toUpperCase();
} 

if (shares.value > 0)
{
    sharesHasText = true;
}

alert_things(stockHasText, sharesHasText);


stock.addEventListener('keyup', () => {

    stockText = stock.value;
    stockHasText = stockText.length > 0;
    stock.value = stock.value.toUpperCase();

    alert_things(stockHasText, sharesHasText);
});


shares.addEventListener('keyup', () => {

    sharesNumber = shares.value;
    sharesHasText = sharesNumber.length > 0;

    alert_things(stockHasText, sharesHasText);
});

