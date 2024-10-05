let dropArea = document.getElementById('drop-area');

dropArea.addEventListener('dragenter', preventDefaults, false);
dropArea.addEventListener('dragleave', preventDefaults, false);
dropArea.addEventListener('dragover', preventDefaults, false);
dropArea.addEventListener('drop', preventDefaults, false);

function preventDefaults(e) {
    e.preventDefault();
    e.stopPropagation();
}

dropArea.addEventListener('drop', handleDrop, false);

function handleDrop(e) {
    let dt = e.dataTransfer;
    let files = dt.files;
    handleFiles(files);
}

function handleFiles(files) {
    let file = files[0];
    if (file && file.type.startsWith('image/')) {
        displayImage(file);
    }
}

function displayImage(file) {
    let gallery = document.getElementById('gallery');
    gallery.innerHTML = '';

    let img = document.createElement('img');
    img.src = URL.createObjectURL(file);
    img.onload = () => {
        URL.revokeObjectURL(img.src);
    };

    gallery.appendChild(img);
}

// Dark/Light mode
const themeToggleButton = document.querySelector('.toggle-theme');

themeToggleButton.addEventListener('click', () => {
    document.body.classList.toggle('dark-mode');
});
