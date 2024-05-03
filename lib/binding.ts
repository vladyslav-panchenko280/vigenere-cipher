const { vigenereEncryption } = require('../build/Release/vigenere_plus');
const fs = require('fs'); 

function vigenereCipher() {
    const args = process.argv.slice(2); 

    if (args.length < 2) {
        console.error("Usage: node vigenereCipher <key> <modificator (--encrypt/--decrypt)>");
        process.exit(1);
    }

    const key = args[0];
    const modificator = args[1];

    if (modificator !== '--encrypt' && modificator !== '--decrypt') {
        console.error("Invalid modificator. Use '--encrypt' or '--decrypt'.");
        process.exit(1);
    }

    if (modificator === '--encrypt') {
        if (!fs.existsSync('env.json')) {
            console.error("Error: 'env.json' does not exist. Please ensure the file is available before encrypting.");
            process.exit(1);
        }
    } else if (modificator === '--decrypt') {
        if (!fs.existsSync('env.enc.json')) {
            console.error("Error: 'env.enc.json' does not exist. Please ensure the file is available before decrypting.");
            process.exit(1);
        }
    }

    try {
        vigenereEncryption(key, modificator);
    } catch (error) {
        console.error("Error during encryption/decryption:", error);
    }
}

vigenereCipher();

export { vigenereCipher };


