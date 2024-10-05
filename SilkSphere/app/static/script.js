let dropArea = document.getElementById('drop-area');
let uploadForm = document.getElementById('uploadForm');
let predictionElement = document.getElementById('prediction');

// Prevent default behaviors on drag events
['dragenter', 'dragover', 'dragleave', 'drop'].forEach(eventName => {
    dropArea.addEventListener(eventName, preventDefaults, false);
});

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
        if (predictionElement) {
            predictionElement.remove();
        }
        let fileInput = document.getElementById('fileElem');
        fileInput.files = files;

        uploadForm.submit();
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
