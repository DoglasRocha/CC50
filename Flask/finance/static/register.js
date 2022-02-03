const alert_things = (textInUsername, 
    textInPassword, 
    textInCPassword, 
    password,
    cPassword) => {

    let regex = new RegExp('[a-zA-Z0-9]{8,}');

    if (!textInUsername && !textInPassword && !textInCPassword) {
        warning.textContent = 'You must fulfill the form!';
    } else if (!textInUsername) {
        warning.textContent = 'You must create a username!';
    } else if (!textInPassword) {
        warning.textContent = 'You must create a password!';
    } else if (!regex.test(password.value)) {
        warning.textContent = 'Your password must have 8 or more characters!';
    } else if (!textInCPassword) {
        warning.textContent = 'You must confirm the password!';
    } else if (password.value !== cPassword.value) {
        warning.textContent = 'The passwords does not match!';
    } else {
        warning.textContent = '';
    }
} 


let username = document.querySelector('#username');
let password = document.querySelector('#password');
let cPassword = document.querySelector('#confirm-password');
let warning = document.querySelector('#warning');

let usernameHasText = false;
let passwordHasText = false;
let cPasswordHasText = false;

if (username.value.length > 0) {
    usernameHasText = true;
} 

if (password.value.length > 0) {
    passwordHasText = true;
} 

if (cPassword.value.length > 0) {
    cPasswordHasText = true;
} 

alert_things(usernameHasText, passwordHasText, cPasswordHasText, 
    password, cPassword);


username.addEventListener('keyup', () => {

    usernameHasText = username.value.length > 0;

    alert_things(usernameHasText, passwordHasText, cPasswordHasText, 
        password, cPassword);
});


password.addEventListener('keyup', () => {

    passwordHasText = password.value.length > 0;

    alert_things(usernameHasText, passwordHasText, cPasswordHasText, 
        password, cPassword);
});


cPassword.addEventListener('keyup', () => {

    cPasswordHasText = cPassword.value.length > 0;

    alert_things(usernameHasText, passwordHasText, cPasswordHasText, 
        password, cPassword);
});