const alert_things = textInMoney => {

    if (!textInMoney)
    {
        warning.textContent = 'You must provide a money amount to withdraw!';
    }
    else
    {
        warning.textContent = '';
    }
} 


let money = document.querySelector('#money');
let warning = document.querySelector('#warning');

let moneyText;
let moneyHasText = false;

if (money.value.length > 0)
{
    moneyHasText = true;
} 

alert_things(moneyHasText);


money.addEventListener('keyup', () => {

    moneyText = money.value;
    moneyHasText = moneyText.length > 0;

    alert_things(moneyHasText);
});
