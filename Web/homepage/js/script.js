const name_switcher = name => {
    switch (name)
    {
        case 'Excalibur':
            name = 'Excalibur (livro)';
            break;

        case 'O Ladrão de Raios':
            name = 'The Lightning Thief';
            break;

        case 'O Mar de Monstros':
            name = 'The Sea of Monsters';
            break;

        case 'A Maldição do Titã':
            name = "The Titan's Curse";
            break;

        case 'A Batalha do Labirinto':
            name = 'The Battle of the Labyrinth';
            break;

        case 'O Último Olimpiano':
            name = 'The Last Olympian';
            break;

        case 'O Herói Perdido':
            name = 'The Lost Hero';
            break;

        case 'O Filho de Netuno':
            name = 'The Son of Neptune';
            break;
    }

    return name;
}

let books = document.querySelectorAll('#book-name');
let remove = document.querySelector('#remove');
let description = document.querySelector('#description');
let image = document.querySelector('#image');
let link = document.querySelector('#link');

books.forEach(book => {
    book.addEventListener('click', () => {
        let name = book.textContent;
        name = name_switcher(name);


        let request = fetch(`https://pt.wikipedia.org/w/api.php?origin=*&action=query&titles=${name}&prop=extracts|pageimages|info&pithumbsize=400&inprop=url&format=json&redirect=`);
        request
            .then(data => data.json())
            .then(data => {
                let pages = data.query.pages
                let keys = Object.keys(pages);

                let page = pages[keys[0]];
                let firstParagraph = page.extract.split('<h2>')[0];
                remove.textContent = '';
                description.innerHTML = firstParagraph;

                let page_link = page.fullurl;
                link.href = page_link;
                link.textContent = 'Wikipedia';

                if (page.thumbnail)
                {   
                    let page_image = page.thumbnail.source;
                    image.src = page_image;
                    image.alt = name;
                }
        });
    });
});