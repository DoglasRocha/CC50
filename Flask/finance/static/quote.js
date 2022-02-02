const alert_things = textInStock => {

    if (!textInStock)
    {
        warning.textContent = 'You must provide a stock symbol!';
    }
    else
    {
        warning.textContent = '';
    }
} 


let stock = document.querySelector('#stock');
let warning = document.querySelector('#warning');

let stockText;
let stockHasText = false;

if (stock.value.length > 0)
{
    stockHasText = true;
    stock.value = stock.value.toUpperCase();
} 

alert_things(stockHasText);


stock.addEventListener('keyup', () => {

    stockText = stock.value;
    stock.value = stockText.toUpperCase();
    stockHasText = stockText.length > 0;

    alert_things(stockHasText);
});
