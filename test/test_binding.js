const fs = require('fs');
const assert = require("assert");
const { execSync } = require('child_process');
require('dotenv').config({ path: './.env.test' });

function simulateVigenereCipher() {
    const originalData = { name: "Bob", surname: "Dawell", nickname: "bobby_dawell100", email: "bobdawell@dell.ch" };
    fs.writeFileSync('env.json', JSON.stringify(originalData, null, 2));

    execSync(`node dist/binding.js ${process.env.KEY} --encrypt`, { stdio: 'inherit' });

    execSync(`node dist/binding.js ${process.env.KEY} --decrypt`, { stdio: 'inherit' });

    const decryptedData = JSON.parse(fs.readFileSync('env.json', 'utf8'));
    assert.deepStrictEqual(originalData, decryptedData, "Decrypted data does not match the original");
}

function testEncryptionDecryption() {
    assert.doesNotThrow(simulateVigenereCipher, undefined, "Encryption/Decryption process threw an exception");
    console.log("Tests passed - everything looks OK!");
}

testEncryptionDecryption();