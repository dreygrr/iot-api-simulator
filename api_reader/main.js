const apiUrl = "https://api.thingspeak.com";
const apiWriteToken = "TG0WAU5CS4XL214F";

const btn = document.querySelector('.btn-led');
const title = document.querySelector('.title');

btn.addEventListener('click', async function() {
    const led = document.querySelector('.led');
    const binary = led.classList.contains('active') ? 0 : 1;

    const resp = await fetch(`${apiUrl}/update?api_key=${apiWriteToken}&field1=${binary}`);
    console.log(resp);
    
    const res = await resp.json();
    console.log(res);

    led.classList.toggle('active');

    btn.classList.toggle('blocked');
    setTimeout(() => btn.classList.toggle('blocked'), 15000);
    
    let i = 0;
    const cooldown = setInterval(() => {
        i++;
        console.log(i);
        title.innerHTML = 'wait ' + (15 - i) + ' seconds';
        
        if (i == 15) {
            clearInterval(cooldown);
            title.innerHTML = 'press';
        } 
    }, 1000 + i);
});
