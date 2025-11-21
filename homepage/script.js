document.addEventListener('DOMContentLoaded', () => {
    const map = {
        low: 1,
        mid: 15,
        max: 999
    };
    const levelSel = document.getElementById('level');

    document.getElementById('spinnerForm').addEventListener('submit', (e) => {
        e.preventDefault();

        const count = map[levelSel.value] ?? 30;

        document.getElementById('spinner').innerHTML =
            `<div class="spinner-grow text-info" role="status">
         <span class="visually-hidden">Loading...</span>
       </div>`.repeat(count);

        document.getElementById('reply').textContent = `${count} spinner${count > 1 ? 's' : ''} shown (${levelSel.value.toUpperCase()})`;
    });
});
